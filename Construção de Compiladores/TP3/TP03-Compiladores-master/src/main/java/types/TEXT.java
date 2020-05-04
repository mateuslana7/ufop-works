package types;

public class TEXT extends Type {

    public static final TEXT T = new TEXT();

    private TEXT() {
    }

    @Override
    public String toString() {
        return "text";
    }
}
