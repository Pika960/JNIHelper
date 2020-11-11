/**
 * This enum provides the names of all colors which can be used in JNIHelper.
 *
 * @author  Gabriel Daenner
 * @version 1.1.0
 */
public enum Colors
{
    /**
     * the color black
     */
    BLACK(0, 30),

    /**
     * the color blue
     */
    BLUE(1, 34),

    /**
     * the color green
     */
    GREEN(2, 32),

    /**
     * the color aqua
     */
    AQUA(3, 36),

    /**
     * the color red
     */
    RED(4, 31),

    /**
     * the color purple
     */
    PURPLE(5, 35),

    /**
     * the color yellow
     */
    YELLOW(6, 33),

    /**
     * the color white
     */
    WHITE(7, 37),

    /**
     * the color gray
     */
    GRAY(8, 37),

    /**
     * the color light blue
     */
    LIGHT_BLUE(9, 34),

    /**
     * the color light green
     */
    LIGHT_GREEN(10, 32),

    /**
     * the color light aqua
     */
    LIGHT_AQUA(11, 36),

    /**
     * the color light red
     */
    LIGHT_RED(12, 31),

    /**
     * the color light purple
     */
    LIGHT_PURPLE(13, 35),

    /**
     * the color light yellow
     */
    LIGHT_YELLOW(14, 33),

    /**
     * the color bright white
     */
    BRIGHT_WHITE(15, 37);

    private final int    colorCodeWindows;
    private final int    colorCodeUnix;
    private final String systemName;

    private Colors(int colorCodeWindows, int colorCodeUnix)
    {
        this.colorCodeWindows = colorCodeWindows;
        this.colorCodeUnix    = colorCodeUnix;
        this.systemName = JNIHelper.getOperatingSystemName().toLowerCase();
    }

    /**
     * get the platform-specific color code
     * @return the platform-specific color code
     */
    public int getColorCode()
    {
        if(systemName.contains("win"))
        {
            return colorCodeWindows;
        }

        else if(systemName.contains("aix") || systemName.contains("bsd")
            || systemName.contains("hp")   || systemName.contains("mac")
            || systemName.contains("nix")  || systemName.contains("nux")
            || systemName.contains("sol"))
        {
            return colorCodeUnix;
        }

        else
        {
            return Integer.MAX_VALUE;
        }
    }
}
