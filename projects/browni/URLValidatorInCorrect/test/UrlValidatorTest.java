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

    public void testRandomTest() {
        int fails = 0;
        int runs = 10;    //Number of tests to run 
        int k = 0;
        int r = 0;
        // set up valid parts
        String[] badUrlsGood = new String[runs];
        String[] goodSchemes = {"http://", "ftp://", "h3t://"};
        String[] goodAuthority = {"www.google.com", "google.com", "0.0.0.0", "255.255.255.255", "go.cc"};
        String[] goodPort = {":80", ":9", ":100", "", "65636"};
        String[] goodPath = {"/test1", "/", "/$23", ""};
        String[] goodOptions = {"/test1", "/$23/test1", "", "/test1//file"};
        String[] goodQueries = {"?action=view", ""};
        String[] badUrlsPoor = new String[runs];
        String[] poorSchemes = {"3ht://", "http:/", "http:"};
        String[] poorAuthority = {"256.256.256.256", "1.2.3.4.", "go.a1a", ".aaa"};
        String[] poorPort = {":-1", ":65a", "::-0"};
        String[] poorPath = {"/..", "/../", "/$23", "/test1//file"};
        String[] poorOptions = {"/#", "/../file", "/#/file"};


        // picks a random value to use as the number of array to use to build the URL
        System.out.println("\nTesting Known Valid Part Inputs:\n");
        for (int i = 0; i < runs; i++) {
            
            int schemeInt = (int) (Math.random() * 2);
            int authorityInt = (int) (Math.random() * 2);
            int portInt = (int) (Math.random() * 3);
            int pathInt = (int) (Math.random() * 2);
            int optionsInt = (int) (Math.random() * 3);
            int queriesInt = (int) (Math.random() * 2);

            // Compose url pieces
            String url = goodSchemes[schemeInt] + goodAuthority[authorityInt] + goodPort[portInt] + goodPath[pathInt] + goodQueries[queriesInt];
            String urlf = poorSchemes[schemeInt] + poorAuthority[authorityInt] + poorPort[portInt] + poorPath[pathInt] + goodQueries[queriesInt];
            UrlValidator validator = new UrlValidator();

            
            boolean valid = validator.isValid(url);
            boolean valid2 = validator.isValid(urlf);
            // if not valid, increase fail count and store url
            if (valid == false) {
                fails++;
                badUrlsGood[k] = url;
                k++;
            }
            if (valid2 == true) {
                fails++;
                badUrlsPoor[r] = urlf;
                r++;
            }
        }
        // result reporting
        System.out.println("\nNumber of Bugs: " + fails + "\n");
        System.out.println("\nGood URLs that failed: \n");
        for (int j = 0; j < badUrlsGood.length; j++) {
            if (badUrlsGood[j] != null) {
                System.out.println(badUrlsGood[j] + "\n");
            }
        }
        System.out.println("\nPoor URLs that passed: \n");
        for (int s = 0; s < badUrlsPoor.length; s++) {
            if (badUrlsPoor[s] != null) {
                System.out.println(badUrlsPoor[s] + "\n");
            }
        }
    }

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
