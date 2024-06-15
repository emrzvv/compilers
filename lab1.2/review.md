% Лабораторная работа № 1.2. «Лексический анализатор
  на основе регулярных выражений»
% 13 марта 2024 г.
% Егор Поршенко, ИУ9-61Б

# Цель работы
Целью данной работы является приобретение навыка разработки простейших лексических анализаторов, работающих на основе поиска в тексте по образцу, заданному регулярным выражением.

# Индивидуальный вариант
- Идентификаторы: последовательности латинских букв и десятичных цифр, оканчивающиеся на цифру.
- Числовые литералы: непустые последовательности десятичных цифр, органиченные знаками «<» и «>».
- Операции: «<=», «=», «==».

# Реализация
Main.java:
```java
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Parser p = new Parser("./test");
        Map<String, ArrayList<ParsedData>> result = p.parse();
        ArrayList<ParsedData> lexemes = result.get("lexemes");
        ArrayList<ParsedData> errors = result.get("errors");

        System.out.println("===============");
        lexemes.forEach(System.out::println);
        System.out.println("===============");
        errors.forEach(System.out::println);
    }
}
```
ParsedData.java:
```java
public class ParsedData {
    public String type;
    public int line;
    public int indent;
    public String token;

    public ParsedData(String type, int line, int indent, String token) {
        this.type = type;
        this.line = line;
        this.indent = indent;
        this.token = token;
    }

    @Override
    public String toString() {
        return type + " (" + line + ", " + indent + "): " + token;
    }
}
```
Parser.java:
```java
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

```
# Тестирование

Входные данные

```
abc123 <= def456 == 789
a b cde
abacaba eee <= <123> = <000> <= bhj0
```

Вывод на `stdout` (если необходимо)

```
===============
ident (1, 1): abc123
operation (1, 8): <=
ident (1, 11): def456
operation (1, 18): ==
ident (1, 21): 789
operation (3, 13): <=
numerical (3, 16): <123>
operation (3, 22): =
numerical (3, 24): <000>
operation (3, 30): <=
ident (3, 33): bhj0
===============
error (2, 1): a
error (2, 3): b
error (2, 5): cde
error (3, 1): abacaba
error (3, 9): eee
```

# Вывод
‹пишете, чему научились›