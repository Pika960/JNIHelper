/**
 * The class TestApp is a minimalistic
 * example application for testing purposes.
 *
 * @author  Gabriel Daenner
 * @version 1.1.0
 */
public class TestApp
{
    //get some colors
    private static int blue   = Colors.LIGHT_BLUE.getColorCode();
    private static int green  = Colors.LIGHT_GREEN.getColorCode();
    private static int red    = Colors.LIGHT_RED.getColorCode();
    private static int yellow = Colors.LIGHT_YELLOW.getColorCode();

    /**
     * main program logic
     * @param args array with command-line arguments
     */
    public static void main(String[] args)
    {
        //check if command-line arguments are provided
        if (args.length > 0)
        {
            if(args[0].equalsIgnoreCase("noMenu"))
            {
                quickTests();
                System.exit(0);
            }
        }

        //values
        boolean inputIsValid  = false;
        int     userInput     = 0;

        //init scanner
        java.util.Scanner scanner = new java.util.Scanner(System.in);

        //always clear screen
        JNIHelper.consoleClear();

        //display menu
        do
        {
            //display welcome message
            System.out.print("JNIHelper TestApp\n\n");

            //display menu entries
            System.out.print("1: Test \"Display system information\"\n");
            System.out.print("2: Test \"Modify/Access Windows Registry\"\n");
            System.out.print("3: Test \"Print colored text\"\n");
            System.out.print("4: Test \"Send argument to host\"\n");
            System.out.print("5: Test \"Sound generation\"\n");
            System.out.print("6: Exit \"TestApp\"\n\n");

            while (true)
            {
                try
                {
                    System.out.print("Please select an option: ");
                    userInput = scanner.nextInt();

                    if (userInput == 6)
                    {
                        break;
                    }

                    else if (userInput > 0 && userInput < 6)
                    {
                        JNIHelper.consoleClear();
                        testCases(userInput);
                        break;
                    }

                    else
                    {
                        System.out.print("Sorry, your input is out of range. Please try again.\n");
                    }
                }
                catch (java.util.InputMismatchException imexc)
                {
                    System.out.print("Sorry, your input contains invalid characters. Please try again.\n");
                    scanner.next();
                }
            }
        } while(userInput != 6);

        System.out.print("Goodbye\n");
    }

    private static void quickTests()
    {
        JNIHelper.printColoredText("Blue\n",   blue);
        JNIHelper.printColoredText("Green\n",  green);
        JNIHelper.printColoredText("Red\n",    red);
        JNIHelper.printColoredText("Yellow\n", yellow);
        JNIHelper.beep(440, 1000);
    }

    private static void testCases(int userInput)
    {
        //run test
        switch (userInput)
        {
            case (1):
            {
                System.out.print("Test 1 - Display system information\n\n");

                System.out.print("This test uses the following methods:\n");
                System.out.print("- consoleClear\n");
                System.out.print("- consolePause\n");
                System.out.print("- getComputerName\n");
                System.out.print("- getOperatingSystemName\n");
                System.out.print("- getSystemMemoryInfo\n");
                System.out.print("- getUserName\n");
                System.out.print("- isElevated\n");
                System.out.print("- isHeadless\n\n");

                int availableSystemMemory = (int)JNIHelper.getSystemMemoryInfo("available", "kb", false);
                int totalSystemMemory     = (int)JNIHelper.getSystemMemoryInfo("total",     "kb", false);
                int spacer                = (int)(Math.log10(totalSystemMemory) + 1);

                String computerName = JNIHelper.getComputerName();
                String isElevated   = JNIHelper.isElevated() ? "Elevated" : "Restricted";
                String isHeadless   = JNIHelper.isHeadless() ? "Headless" : "Graphical";
                String systemName   = JNIHelper.getOperatingSystemName();
                String userName     = JNIHelper.getUserName();

                System.out.printf("Name of the current user:             %s\n",   userName);
                System.out.printf("Name of the current computer:         %s\n",   computerName);
                System.out.printf("Name of the current operating system: %s\n\n", systemName);
                System.out.printf("Current elevation level:              %s\n",   isElevated);
                System.out.printf("Current supported application target: %s\n\n", isHeadless);
                System.out.printf("There are %" + spacer + "d free  KB of physical memory.\n",   availableSystemMemory);
                System.out.printf("There are %" + spacer + "d total KB of physical memory.\n\n", totalSystemMemory);

                JNIHelper.consolePause();
                JNIHelper.consoleClear();
            } break;

            case (2):
            {
                System.out.print("Test 2 - Modify/Access Windows Registry\n\n");

                System.out.print("This test uses the following methods:\n");
                System.out.print("- consoleClear\n");
                System.out.print("- consolePause\n");
                System.out.print("- deleteRegistryKey\n");
                System.out.print("- deleteRegistryValue\n");
                System.out.print("- getOperatingSystemName\n");
                System.out.print("- getRegistryValueNumeric\n");
                System.out.print("- getRegistryValueText\n");
                System.out.print("- setRegistryValueNumeric\n");
                System.out.print("- setRegistryValueText\n\n");

                String hkcu       = HKEY.HKEY_CURRENT_USER.toString();
                String subkey     = "SOFTWARE\\JNIHelper";
                String systemName = JNIHelper.getOperatingSystemName().toLowerCase();

                if (systemName.contains("win"))
                {
                    boolean error_success = false;
                    int     result_number = Integer.MIN_VALUE;
                    String  result_string = "Error";

                    System.out.print("This test uses the registry path: ");
                    System.out.print("\"" + hkcu + "\\" + subkey + "\"\n\n");
                    error_success = JNIHelper.setRegistryValueNumeric(hkcu, subkey, "TestNumeric", 42);
                    System.out.printf("Writing numeric value. Status: %s\n",   error_success ? "Success" : "Failed");
                    result_number = JNIHelper.getRegistryValueNumeric(hkcu, subkey, "TestNumeric");
                    System.out.printf("Reading numeric value. Result: %d\n",   result_number);
                    error_success = JNIHelper.setRegistryValueText(hkcu, subkey, "TestString", "Hello World");
                    System.out.printf("Writing text value.    Status: %s\n",   error_success ? "Success" : "Failed");
                    result_string = JNIHelper.getRegistryValueText(hkcu, subkey, "TestString");
                    System.out.printf("Reading text value.    Result: %s\n",   result_string);
                    error_success = JNIHelper.deleteRegistryValue(hkcu, subkey, "TestNumeric");
                    System.out.printf("Deleting value.        Status: %s\n",   error_success ? "Success" : "Failed");
                    error_success = JNIHelper.deleteRegistryValue(hkcu, subkey, "TestString");
                    System.out.printf("Deleting value.        Status: %s\n",   error_success ? "Success" : "Failed");
                    error_success = JNIHelper.deleteRegistryKey(hkcu, subkey);
                    System.out.printf("Deleting key.          Status: %s\n\n", error_success ? "Success" : "Failed");
                }

                else
                {
                    System.out.print("It appears that this computer is not running Windows.\n");
                    System.out.print("For this reason this test is skipped.\n\n");
                }

                JNIHelper.consolePause();
                JNIHelper.consoleClear();
            } break;

            case (3):
            {
                System.out.print("Test 3 - Print colored text\n\n");

                System.out.print("This test uses the following methods:\n");
                System.out.print("- consoleClear\n");
                System.out.print("- consolePause\n");
                System.out.print("- printColoredText\n\n");

                JNIHelper.printColoredText("I am ",        blue);
                JNIHelper.printColoredText("a very ",      green);
                JNIHelper.printColoredText("colorful ",    red);
                JNIHelper.printColoredText("message.\n\n", yellow);

                JNIHelper.consolePause();
                JNIHelper.consoleClear();
            } break;

            case (4):
            {
                System.out.print("Test 4 - Send argument to host\n\n");

                System.out.print("This test uses the following methods:\n");
                System.out.print("- consoleClear\n");
                System.out.print("- consolePause\n");
                System.out.print("- sendStringToNative\n\n");

                System.out.print("Executing command: \"java -version\"\n\n");
                JNIHelper.sendStringToNative("java --version");
                System.out.print("\n");

                JNIHelper.consolePause();
                JNIHelper.consoleClear();
            } break;

            case (5):
            {
                System.out.print("Test 5 - Sound generation\n\n");

                System.out.print("This test uses the following methods:\n");
                System.out.print("- beep\n");
                System.out.print("- consoleClear\n");
                System.out.print("- consolePause\n");
                System.out.print("- isHeadless\n\n");

                if (JNIHelper.isHeadless())
                {
                    System.out.print("It appears that this is a headless device.\n");
                    System.out.print("For this reason this test is skipped.\n\n");
                }

                else
                {
                    System.out.print("Playing: Tetris Theme\n\n");
                    JNIHelper.beep(convertNoteToFrequency(10), 440);
                    JNIHelper.beep(convertNoteToFrequency( 5), 220);
                    JNIHelper.beep(convertNoteToFrequency( 6), 220);
                    JNIHelper.beep(convertNoteToFrequency( 8), 440);
                    JNIHelper.beep(convertNoteToFrequency( 6), 220);
                    JNIHelper.beep(convertNoteToFrequency( 5), 220);
                    JNIHelper.beep(convertNoteToFrequency( 3), 440);
                    JNIHelper.beep(convertNoteToFrequency( 3), 220);
                    JNIHelper.beep(convertNoteToFrequency( 6), 220);
                    JNIHelper.beep(convertNoteToFrequency(10), 440);
                    JNIHelper.beep(convertNoteToFrequency( 8), 220);
                    JNIHelper.beep(convertNoteToFrequency( 6), 220);
                    JNIHelper.beep(convertNoteToFrequency( 5), 660);
                    JNIHelper.beep(convertNoteToFrequency( 6), 220);
                    JNIHelper.beep(convertNoteToFrequency( 8), 440);
                    JNIHelper.beep(convertNoteToFrequency(10), 440);
                    JNIHelper.beep(convertNoteToFrequency( 6), 440);
                    JNIHelper.beep(convertNoteToFrequency( 3), 440);
                    JNIHelper.beep(convertNoteToFrequency( 3), 440);
                }

                JNIHelper.consolePause();
                JNIHelper.consoleClear();
            } break;
        }
    }

    private static int convertNoteToFrequency(int note)
    {
        float frequency = 2.0f;
        frequency = (float)(Math.pow(frequency, (note / 12.0f)));
        frequency = frequency * 440;

        return (int)frequency;
    }
}
