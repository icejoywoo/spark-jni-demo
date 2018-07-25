import java.io.Serializable;

public class Base64 implements Serializable {
    static {
        System.loadLibrary("base64");
    }

    private String name;

    public Base64() {
        name = "base64";
    }

    public native static String encode(String data);
    public native static String decode(String data);

    public static void main(String[] args) {
        System.out.println(Base64.encode("test_string"));
        System.out.println(Base64.decode("dGVzdF9zdHJpbmc="));
    }
}
