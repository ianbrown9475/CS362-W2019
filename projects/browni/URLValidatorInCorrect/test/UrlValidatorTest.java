import junit.framework.TestCase;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

// You can use this as a skeleton for your 3 different test approach
// It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {

    public UrlValidatorTest(String testName) {
        super(testName);
    }

    public void testManualTest() {
        // You can use this function to implement your manual testing
    }

    public void testYourFirstPartition() {
        // You can use this function to implement your First Partition testing
    }

    public void testYourSecondPartition() {
        // You can use this function to implement your Second Partition testing
    }
    // You need to create more test cases for your Partitions if you need to

    /**
     * Programming based testing
     * @throws FileNotFoundException if problem occurs when loading csv file
     */
    public void testIsValid() throws FileNotFoundException {
      List<List<String>> urlTestCases = new ArrayList<>();

        String fileName = "test/urls.csv";
        Scanner scanner = new Scanner(new File(fileName));
        while (scanner.hasNext()) {
            String line = scanner.nextLine();
            List<String> list = Arrays.asList(line.split(","));
          urlTestCases.add(list);
        }
        scanner.close();

        UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        urlTestCases.forEach((list) -> {
            boolean res = urlValidator.isValid(list.get(0));
            assertEquals(list.get(2), list.get(1).equals("true"), res);
        });

        // Test a null URL
        assertFalse(urlValidator.isValid(null));
    }
}
