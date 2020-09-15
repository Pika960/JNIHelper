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
    //get some colors
    private static int blue   = JNIHelper.convertToSystemColorCode(Colors.light_blue);
    private static int green  = JNIHelper.convertToSystemColorCode(Colors.light_green);
    private static int red    = JNIHelper.convertToSystemColorCode(Colors.light_red);
    private static int yellow = JNIHelper.convertToSystemColorCode(Colors.light_yellow);

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
            System.out.print("1: Test \"Colored Text\"\n");
            System.out.print("2: Test \"Pause/Wait for user input\"\n");
            System.out.print("3: Test \"Clear console window\"\n");
            System.out.print("4: Test \"Beep (minimalistic)\"\n");
            System.out.print("5: Test \"Beep (complex)\"\n");
            System.out.print("6: Exit TestApp\n\n");

            while (!inputIsValid)
            {
                try
                {
                    System.out.print("Please select an option: ");
                    userInput = scanner.nextInt();

                    if (userInput != 6)
                    {
                        JNIHelper.consoleClear();
                        testCases(userInput);
                    }

                    inputIsValid  = true;
                }
                catch (Exception exc)
                {
                    System.out.print("Sorry, something with your input is wrong. Please try again\n");
                    scanner.next();
                }
            }

            inputIsValid = false;
        } while(userInput != 6);
    }

    private static void quickTests()
    {
        JNIHelper.printColoredText("Blue\n",     blue);
        JNIHelper.printColoredText("Green\n",    green);
        JNIHelper.printColoredText("Red\n",      red);
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
                System.out.print("Test 1 - Colored Text\n\n");

                JNIHelper.printColoredText("Blue\n",     blue);
                JNIHelper.printColoredText("Green\n",    green);
                JNIHelper.printColoredText("Red\n",      red);
                JNIHelper.printColoredText("Yellow\n\n", yellow);

                JNIHelper.consolePause();
                JNIHelper.consoleClear();
            } break;

            case (2):
            {
                System.out.print("Test 2 - Pause/Wait for user input\n\n");

                JNIHelper.consolePause();
                JNIHelper.consoleClear();
            } break;

            case (3):
            {
                System.out.print("Test 3 - Clear console window\n\n");
                System.out.print("Screen will be cleared in 2 seconds...\n");

                try
                {
                    Thread.sleep(2000);
                }
                catch(InterruptedException ex)
                {
                    Thread.currentThread().interrupt();
                }

                JNIHelper.consoleClear();

                System.out.print("Screen is cleared.\n\n");

                JNIHelper.consolePause();
                JNIHelper.consoleClear();
            } break;

            case (4):
            {
                System.out.print("Test 4 - Beep (minimalistic)\n\n");

                JNIHelper.beep(440, 1000);
                JNIHelper.consolePause();
                JNIHelper.consoleClear();
            } break;

            case (5):
            {
                System.out.print("Test 5 - Beep (complex)\n\n");

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
