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
    black,

    /**
     * the color blue
     */
    blue,

    /**
     * the color green
     */
    green,

    /**
     * the color aqua
     */
    aqua,

    /**
     * the color red
     */
    red,

    /**
     * the color purple
     */
    purple,

    /**
     * the color yellow
     */
    yellow,

    /**
     * the color white
     */
    white,

    /**
     * the color gray
     */
    gray,

    /**
     * the color light blue
     */
    light_blue,

    /**
     * the color light green
     */
    light_green,

    /**
     * the color light aqua
     */
    light_aqua,

    /**
     * the color light red
     */
    light_red,

    /**
     * the color light purple
     */
    light_purple,

    /**
     * the color light yellow
     */
    light_yellow,

    /**
     * the color bright white
     */
    bright_white;

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
                case black:        return  0;
                case blue:         return  1;
                case green:        return  2;
                case aqua:         return  3;
                case red:          return  4;
                case purple:       return  5;
                case yellow:       return  6;
                case white:        return  7;
                case gray:         return  8;
                case light_blue:   return  9;
                case light_green:  return 10;
                case light_aqua:   return 11;
                case light_red:    return 12;
                case light_purple: return 13;
                case light_yellow: return 14;
                case bright_white: return 15;
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
                case black:        return 30;
                case blue:         return 34;
                case green:        return 32;
                case aqua:         return 36;
                case red:          return 31;
                case purple:       return 35;
                case yellow:       return 33;
                case white:        return 37;
                case gray:         return 37;
                case light_blue:   return 34;
                case light_green:  return 32;
                case light_aqua:   return 36;
                case light_red:    return 31;
                case light_purple: return 35;
                case light_yellow: return 33;
                case bright_white: return 37;
                default:           return 30;
            }
        }

        else
        {
            return Integer.MAX_VALUE;
        }
    }
}
