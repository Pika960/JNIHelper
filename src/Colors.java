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
    BLACK,

    /**
     * the color blue
     */
    BLUE,

    /**
     * the color green
     */
    GREEN,

    /**
     * the color aqua
     */
    AQUA,

    /**
     * the color red
     */
    RED,

    /**
     * the color purple
     */
    PURPLE,

    /**
     * the color yellow
     */
    YELLOW,

    /**
     * the color white
     */
    WHITE,

    /**
     * the color gray
     */
    GRAY,

    /**
     * the color light blue
     */
    LIGHT_BLUE,

    /**
     * the color light green
     */
    LIGHT_GREEN,

    /**
     * the color light aqua
     */
    LIGHT_AQUA,

    /**
     * the color light red
     */
    LIGHT_RED,

    /**
     * the color light purple
     */
    LIGHT_PURPLE,

    /**
     * the color light yellow
     */
    LIGHT_YELLOW,

    /**
     * the color bright white
     */
    BRIGHT_WHITE;

    /**
     * assigns a numeric value to the enum
     * @return the platform-specific color code
     */
    public int getColorCode()
    {
        String systemName = JNIHelper.getOperatingSystemName().toLowerCase();

        if(systemName.contains("win"))
        {
            switch(this)
            {
                case BLACK:        return  0;
                case BLUE:         return  1;
                case GREEN:        return  2;
                case AQUA:         return  3;
                case RED:          return  4;
                case PURPLE:       return  5;
                case YELLOW:       return  6;
                case WHITE:        return  7;
                case GRAY:         return  8;
                case LIGHT_BLUE:   return  9;
                case LIGHT_GREEN:  return 10;
                case LIGHT_AQUA:   return 11;
                case LIGHT_RED:    return 12;
                case LIGHT_PURPLE: return 13;
                case LIGHT_YELLOW: return 14;
                case BRIGHT_WHITE: return 15;
                default:           return  0;
            }
        }

        else if(systemName.contains("aix") || systemName.contains("bsd")
            || systemName.contains("hp")   || systemName.contains("mac")
            || systemName.contains("nix")  || systemName.contains("nux")
            || systemName.contains("sol"))
        {
            switch(this)
            {
                case BLACK:        return 30;
                case BLUE:         return 34;
                case GREEN:        return 32;
                case AQUA:         return 36;
                case RED:          return 31;
                case PURPLE:       return 35;
                case YELLOW:       return 33;
                case WHITE:        return 37;
                case GRAY:         return 37;
                case LIGHT_BLUE:   return 34;
                case LIGHT_GREEN:  return 32;
                case LIGHT_AQUA:   return 36;
                case LIGHT_RED:    return 31;
                case LIGHT_PURPLE: return 35;
                case LIGHT_YELLOW: return 33;
                case BRIGHT_WHITE: return 37;
                default:           return 30;
            }
        }

        else
        {
            return Integer.MAX_VALUE;
        }
    }
}
