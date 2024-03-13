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