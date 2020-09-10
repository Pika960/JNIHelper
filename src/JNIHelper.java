/**
 * The class JNIHelper is a bride class which provides
 * native methods for interaction with the Bash or the
 * Windows Command Prompt (CMD).
 *
 * @author  Gabriel Daenner
 * @version 1.0
 * @since   2020-03-10
 */
public class JNIHelper
{
    /*
        tell java to load the native library file (plattform independent)
        JNIHelper.class and CLib.dll/libCLib.so have to be in the same folder
    */
    static
    {
        java.io.File library = new java.io.File(System.mapLibraryName("CLib"));
        System.load(library.getAbsolutePath());
    }

    /**
     * convertToSystemColorCode converts the color to the specific code.
     * @param colors the name of the color
     * @return the system specific code
     */
    public static int convertToSystemColorCode(Colors color)
    {
        /*
            list of color codes on windows
            black        = 0,  blue          = 1, green         = 2,  aqua         = 3,
            red          = 4,  purple        = 5, yellow        = 6,  white        = 7,
            gray         = 8,  light_blue    = 9, light_green   = 10, light_aqua   = 11,
            light_red    = 12, light_purple = 13, light_yellow  = 14, bright_white = 15

            list of color codes on unix like systems
            black = 30, red     = 31, green = 32, yellow = 33,
            blue  = 34, magenta = 35, cyan  = 36, white  = 37
        */

        String systemName = System.getProperty("os.name").toLowerCase();

        if(systemName.contains("win"))
        {
                 if(color == Colors.black)        return  0;
            else if(color == Colors.blue)         return  1;
            else if(color == Colors.green)        return  2;
            else if(color == Colors.aqua)         return  3;
            else if(color == Colors.red)          return  4;
            else if(color == Colors.purple)       return  5;
            else if(color == Colors.yellow)       return  6;
            else if(color == Colors.white)        return  7;
            else if(color == Colors.gray)         return  8;
            else if(color == Colors.light_blue)   return  9;
            else if(color == Colors.light_green)  return 10;
            else if(color == Colors.light_aqua)   return 11;
            else if(color == Colors.light_red)    return 12;
            else if(color == Colors.light_purple) return 13;
            else if(color == Colors.light_yellow) return 14;
            else if(color == Colors.bright_white) return 15;
            else                                  return  0;
        }

        else if(systemName.contains("nix") || systemName.contains("nux")
            || systemName.contains("aix"))
        {
                 if(color == Colors.black)        return 30;
            else if(color == Colors.blue)         return 34;
            else if(color == Colors.green)        return 32;
            else if(color == Colors.aqua)         return 36;
            else if(color == Colors.red)          return 31;
            else if(color == Colors.purple)       return 35;
            else if(color == Colors.yellow)       return 33;
            else if(color == Colors.white)        return 37;
            else if(color == Colors.gray)         return 37;
            else if(color == Colors.light_blue)   return 34;
            else if(color == Colors.light_green)  return 32;
            else if(color == Colors.light_aqua)   return 36;
            else if(color == Colors.light_red)    return 31;
            else if(color == Colors.light_purple) return 35;
            else if(color == Colors.light_yellow) return 33;
            else if(color == Colors.bright_white) return 37;
            else                                  return 30;
        }

        else
        {
            return Integer.MAX_VALUE;
        }
    }

    /**
     * wipes the content on the current used bash- or cmd-window
     */
    public static native void consoleClear();

    /**
     * pauses the application until a key is pressed
     */
    public static native void consolePause();

    /**
     * prints text in a specific color on the current used bash- or cmd-window
     * @param colorCode colorCode of the text (decimal)
     */
    public static native void printColoredText(String str, int colorCode);

    /**
     * sends a string from the application to the used conhost
     * @param arg String argument for the conhost
     */
    public static native void sendStringToNative(String arg);
}
