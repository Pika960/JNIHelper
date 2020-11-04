/**
 * The class JNIHelper is a bride class which provides
 * native methods for interaction with the Bash or the
 * Windows Command Prompt (CMD).
 *
 * @author  Gabriel Daenner
 * @version 1.1.0
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
     * checks if the application is running with elevated privileges
     * @return true if application is running with elevated privileges, otherwise false
     */
    public static native boolean isElevated();

    /**
     * get information about the system memory usage
     * @param type defines which information will be returned, can be "available" or "total"
     * @param unitMode controls the format for units, can be "kb", "mb" or "gb"
     * @param round if set to true output will be rounded to two decimal places
     * @return the memory information according to the specified configuration
     */
    public static native double getSystemMemoryInfo(String type, String unitMode, boolean round);

    /**
     * retrieves the data for the specified registry value as a numeric value (DWORD)
     * @param hkey the name of a handle to an open registry key
     * @param subkey the path of a registry key relative to the key specified by the hkey parameter
     * @param value the name of the registry value
     * @return the data of the specified registry key (ErrorCode = -1)
     */
    public static native int getRegistryValueNumeric(String hkey, String subkey, String value);

    /**
     * get the hostname of the local computer
     * @return the hostname of the local computer
     */
    public static native String getComputerName();

    /**
     * get the name of the currently running operating system
     * @return the the name of the currently running operating system
     */
    public static native String getOperatingSystemName();

    /**
     * retrieves the data for the specified registry value as a text string
     * @param hkey the name of a handle to an open registry key
     * @param subkey the path of a registry key relative to the key specified by the hkey parameter
     * @param value the name of the registry value
     * @return the data of the specified registry key (ErrorCode = "Undefinded")
     */
    public static native String getRegistryValueText(String hkey, String subkey, String value);

    /**
     * get the name of the user associated with the current thread
     * @return the name of the user associated with the current thread
     */
    public static native String getUserName();

    /**
     * generates simple tones on the speaker
     * @param frequency frequency of the sound, in hertz
     * @param duration duration of the sound, in milliseconds
     */
    public static native void beep(int frequency, int duration);

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
     * @param str the String to be printed
     * @param colorCode colorCode of the text (decimal)
     */
    public static native void printColoredText(String str, int colorCode);

    /**
     * sends a string from the application to the used conhost
     * @param arg String argument for the conhost
     */
    public static native void sendStringToNative(String arg);
}
