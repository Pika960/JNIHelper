/**
 * The class TestApp is a minimalistic
 * example application for testing purposes.
 *
 * @author  Gabriel Daenner
 * @version 1.0
 * @since   2020-03-10
 */
public class TestApp
{
    public static void main(String[] args)
    {
        //get some colors
        int blue   = JNIHelper.convertToSystemColorCode(Colors.light_blue);
        int green  = JNIHelper.convertToSystemColorCode(Colors.light_green);
        int red    = JNIHelper.convertToSystemColorCode(Colors.light_red);
        int yellow = JNIHelper.convertToSystemColorCode(Colors.light_yellow);

        //print some text
        JNIHelper.printColoredText("Blue\n",   blue);
        JNIHelper.printColoredText("Green\n",  green);
        JNIHelper.printColoredText("Red\n",    red);
        JNIHelper.printColoredText("Yellow\n", yellow);
        JNIHelper.consolePause();
        JNIHelper.consoleClear();
        JNIHelper.printColoredText("Blue\n",   blue);
        JNIHelper.printColoredText("Green\n",  green);
        JNIHelper.printColoredText("Red\n",    red);
        JNIHelper.printColoredText("Yellow\n", yellow);
    }
}
