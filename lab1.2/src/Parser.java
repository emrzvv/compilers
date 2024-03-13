import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
public class Parser {
    private ArrayList<String> lines;
    private int currentIdx;
    private String currentLine;

    public Parser(String filename) {
        try {
            this.lines = new ArrayList<String>(Files.readAllLines(Paths.get(filename)));
        } catch (IOException e) {
            e.printStackTrace();
        }
        this.currentIdx = 0;
        this.currentLine = lines.getFirst();
    }

    public Map<String, ArrayList<ParsedData>> parse() {
        ArrayList<ParsedData> errors = new ArrayList<>();
        ArrayList<ParsedData> lexemes = new ArrayList<>();

        Map<String, String> patterns = Map.of(
                "ident", "[a-zA-Z\\d]*\\d",
                "numerical", "<[\\d]+>",
                "operation", "(=(?!=))|(==)|(<=)"
        );

        for (int i = 0; i < lines.size(); ++i) {
            currentLine = rightTrim(lines.get(i));
            currentIdx = 0;
            while (!currentLine.isEmpty()) {
//                System.out.println(currentLine);
                if (currentLine.charAt(0) == ' ') {
                    skipSpaces();
                } else {
                    String ident = "[a-zA-Z\\d]*\\d";
                    String numerical = "<[\\d]+>";
                    String operation = "(=(?!=))|(==)|(<=)";
                    String error = "[\\S]+";
                    String pattern = "(?<ident>^"+ident+")|(?<numerical>^"+numerical+")|(?<operation>^"+operation+")|(?<error>^"+error+")";
                    Pattern p = Pattern.compile(pattern);
                    Matcher m = p.matcher(currentLine);
                    if (m.find()) {
                        if (m.group("ident") != null) {
                            String result = m.group("ident");
                            skip(result.length());
                            ParsedData toAdd = new ParsedData("ident", i + 1, currentIdx - result.length() + 1, result);
                            lexemes.add(toAdd);
                        } else if (m.group("numerical") != null) {
                            String result = m.group("numerical");
                            skip(result.length());
                            ParsedData toAdd = new ParsedData("numerical", i + 1, currentIdx - result.length() + 1, result);
                            lexemes.add(toAdd);
                        } else if (m.group("operation") != null) {
                            String result = m.group("operation");
                            skip(result.length());
                            ParsedData toAdd = new ParsedData("operation", i + 1, currentIdx - result.length() + 1, result);
                            lexemes.add(toAdd);
                        } else if (m.group("error") != null) {
                            String result = m.group("error");
                            skip(result.length());
                            ParsedData toAdd = new ParsedData("error", i + 1, currentIdx - result.length() + 1, result);
                            errors.add(toAdd);
                        }
                    } else {
                        System.out.println("ERROR");
                        System.out.println(currentLine);
                        System.out.println(currentIdx);
                        System.out.println("==========");
                    }
                }
            }
        }

        return Map.of(
                "lexemes", lexemes,
                "errors", errors
        );
    }

    private static String leftTrim(String src) {
        return src.replaceAll("^\\s+", "");
    }

    private static String rightTrim(String src) {
        return src.replaceAll("\\s+$", "");
    }

    private void skipSpaces() {
        String updated = leftTrim(currentLine);
        currentIdx += (currentLine.length() - updated.length());
        currentLine = updated;
    }

    private void skip(int amount) {
        currentIdx += amount;
        currentLine = currentLine.substring(amount);
    }
}
