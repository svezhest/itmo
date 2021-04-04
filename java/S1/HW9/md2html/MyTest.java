package md2html;

public class MyTest {
    public static void main(String[] args) {
        StringBuilder sb = new StringBuilder();
        new HtmlParser(new StringBuilder("**cdiv[yd `bp _nfisdjkk --eztghceaepyz-- o_ li`](vbnm`zzt--ttqz_ecpvyrhld_\n" +
                "c-- ic` )ua**")).toHtml(sb);
        System.out.println(sb.toString());
    }
}
