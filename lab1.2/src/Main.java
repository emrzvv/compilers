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