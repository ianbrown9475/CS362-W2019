import junit.framework.AssertionFailedError;
import junit.framework.TestCase;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

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
     *
     * @throws IOException if problem occurs when loading file or URL
     */
    public void testIsValid() throws IOException {
        UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        List<AssertionFailedError> errors = new ArrayList<>();

        // Test a null URL
        try {
            assertFalse(urlValidator.isValid(null));
        } catch (AssertionFailedError e) {
            errors.add(e);
        }

        // Test URLs from test/urls.csv file
        List<List<String>> urlTestCases = new ArrayList<>();
        String fileName = "test/urls.csv";
        Scanner scanner = new Scanner(new File(fileName));
        while (scanner.hasNext()) {
            String line = scanner.nextLine();
            List<String> list = Arrays.asList(line.split(","));
            urlTestCases.add(list);
        }
        scanner.close();

        urlTestCases.forEach((list) -> {
            boolean res = urlValidator.isValid(list.get(0));
            try {
                assertEquals(list.get(2) + ". URL: \"" + list.get(0) + "\"", list.get(1).equals("true"), res);
            } catch (AssertionFailedError e) {
                errors.add(e);
            }
        });
        System.out.println("Tested " + urlTestCases.size() + " URLs from file: " + fileName);

        // Test URLs from remote web pages
        final String[] REMOTE_URLS = {
                "https://oregonstate.edu",
                "https://eecs.oregonstate.edu",
                "https://facebook.com",
                "https://github.com"
        };
        final String URL_REGEX = "(href|src)=\"(http|https|ftp)://[^\" ]+\"";

        for (String remoteUrl : REMOTE_URLS) {
            Pattern pattern = Pattern.compile(URL_REGEX);
            URL remoteWebPageUrl = new URL(remoteUrl);

            String remoteWebPageString;
            try {
                remoteWebPageString = new Scanner(remoteWebPageUrl.openStream()).useDelimiter("\\A").next();
            } catch (Exception e) {
                System.err.println("Could not get URLs from \"" + remoteUrl + "\". Exception: " + e);
                continue;
            }
            Matcher matcher = pattern.matcher(remoteWebPageString);

            List<String> remoteWebPageUrls = new ArrayList<>();
            while (matcher.find()) {
                String match = matcher.group();
                match = match.replaceAll("href=", "");
                match = match.replaceAll("src=", "");
                match = match.replaceAll("\"", "");
                remoteWebPageUrls.add(match);
            }

            remoteWebPageUrls.forEach(url -> {
                boolean res = urlValidator.isValid(url);
                try {
                    assertTrue("URL from webPage: \"" + url + "\"", res);
                } catch (AssertionFailedError e) {
                    errors.add(e);
                }
            });
            System.out.println("Tested " + remoteWebPageUrls.size() + " URLs from remote page: " + remoteUrl);
        }
        if (errors.size() > 0) {
            errors.forEach(e -> System.err.println(e.toString()));
            fail("Errors were found");
        }
    }
}
