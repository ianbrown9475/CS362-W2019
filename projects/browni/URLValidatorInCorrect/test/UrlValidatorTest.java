

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   /* Manual testing functions */
   
   public void testManualTestDefault()
   {
       UrlValidator urlValidator = new UrlValidator();
       assertTrue(urlValidator.isValid("http://www.google.com"));
	   
       assertFalse(urlValidator.isValid("http://www.goo gle.com"));
       assertFalse(urlValidator.isValid("http:www.google.com"));
	   assertFalse(urlValidator.isValid("http://google/com"));
	   
	   //double slashes
	   assertTrue(urlValidator.isValid("http://www.google.com/testpath5"));
	   assertTrue(urlValidator.isValid("http://www.google.com/test/path"));
	   //assertFalse(urlValidator.isValid("http://www.google.com/wrong//path"));
	   
	   //default schemes
	   assertTrue(urlValidator.isValid("http://www.google.com"));
	   assertTrue(urlValidator.isValid("https://www.google.com"));
	   assertTrue(urlValidator.isValid("ftp://www.google.com"));
	   assertFalse(urlValidator.isValid("htpt://www.google.com"));
	   assertFalse(urlValidator.isValid("htp://www.google.com"));
	   assertFalse(urlValidator.isValid("wrong://www.google.com"));
	   
	   //by default local URLs should not validate
       assertFalse(urlValidator.isValid("http://localhost"));
       assertFalse(urlValidator.isValid("http://localhost/test/index.html"));
	   
       //Port Limits
	   assertTrue(urlValidator.isValid("http://www.google.com:88"));
	   assertTrue(urlValidator.isValid("http://www.google.com:65535")); //last valid port
	   assertFalse(urlValidator.isValid("http://www.google.com:65536")); //first invalid port
	   assertFalse(urlValidator.isValid("http://www.google.com:70000")); 
	   
	   
       
   }
   

   public void testManualTestNoFrag()
   {
       UrlValidator urlValidator = new UrlValidator(UrlValidator.NO_FRAGMENTS);
       assertTrue(urlValidator.isValid("http://www.google.com"));
       assertFalse(urlValidator.isValid("http://www.google")); //don't know if this should qualify as a fragment or not; it passes
       assertFalse(urlValidator.isValid("www.google.com"));
	   
   }

   public void testManualTestSchemes()
   {
	   String[] schemes = {"test"};
       UrlValidator urlValidator = new UrlValidator(schemes);
	   
       assertTrue(urlValidator.isValid("test://www.passedinschemes.com"));
       assertFalse(urlValidator.isValid("test//www.passedinschemes.com"));
       assertFalse(urlValidator.isValid("test:www.passedinschemes.com"));
       assertTrue(urlValidator.isValid("http://www.google.com")); //control; no longer works when schemes passed in. 
       
       
	   urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
       assertTrue(urlValidator.isValid("http://www.google.com")); //control
       assertTrue(urlValidator.isValid("htpt://www.google.com"));
	   assertTrue(urlValidator.isValid("htp://www.google.com"));
	   assertTrue(urlValidator.isValid("wrong://www.google.com"));
   }
   
   public void testManualTestTwoSlashes()
   {
       UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_2_SLASHES);
       assertTrue(urlValidator.isValid("http://www.google.com")); //control
       
       assertTrue(urlValidator.isValid("http://www.google.com/test//case/"));
       assertFalse(urlValidator.isValid("http://www.google.com/../"));
       assertFalse(urlValidator.isValid("http://www.google.com//"));
       
	   
   }
   
   public void testManualTestLocal()
   {
       UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);
       assertTrue(urlValidator.isValid("http://localhost"));
       assertTrue(urlValidator.isValid("http://hostname"));
       assertTrue(urlValidator.isValid("http://localhost/test/index.html"));
       assertTrue(urlValidator.isValid("http://www.google.com")); //control should still validate
       
       assertFalse(urlValidator.isValid("http://broke.hostname/test/index.html"));

   }
   
   /*end manual testing functions*/
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
    int fails = 0;
    int runs = 10;    // change as needed for loop count
    int k = 0;
	int r = 0;
    // set up valid parts
    String[] badUrlsGood = new String[runs];
    String[] goodSchemes = {"http://", "", "ftp://", "h3t://"};
    String[] goodAuthority = {"www.google.com", "google.com", "0.0.0.0", "255.255.255.255", "go.cc"};
    String[] goodPort = {":80", ":9", ":100", "", "65636"};
    String[] goodPath = {"/test1", "/", "/$23", ""};
    String[] goodOptions = {"/test1", "/$23/test1", "", "/test1//file"};
    String[] goodQueries = {"?action=view", ""};
	String[] badUrlsPoor = new String[runs];
	String[] poorSchemes = {"3ht://", "http:/", "http:"};
    String[] poorAuthority = {"256.256.256.256", "1.2.3.4.", "go.a1a", ".aaa"};
    String[] poorPort = {":-1", ":65a"};
    String[] poorPath = {"/..", "/../", "/$23", "/test1//file"};
    String[] poorOptions = {"/#", "/../file", "/#/file"};
    

    // randomize valid each round and loop through "runs" times
    System.out.println("\nTesting Known Valid Part Inputs:\n");
    for(int i = 0; i < runs; i++) {
      // randomize
      int schemeInt = (int) (Math.random() * 2);
      int authorityInt = (int) (Math.random() * 2);
      int portInt = (int) (Math.random() * 3);
      int pathInt = (int) (Math.random() * 2);
      int optionsInt = (int) (Math.random() * 3);
      int queriesInt = (int) (Math.random() *2);

      // make string of valid parts in valid order
      String url = goodSchemes[schemeInt] + goodAuthority[authorityInt] + goodPort[portInt] + goodPath[pathInt] + goodQueries[queriesInt];
	  String urlf = poorSchemes[schemeInt] + poorAuthority[authorityInt] + poorPort[portInt] + poorPath[pathInt] + goodQueries[queriesInt];
      UrlValidator validator = new UrlValidator();

      // check if it was marked valid
      boolean valid = validator.isValid(url);
	  boolean valid2 = validator.isValid(urlf);	
      // if not valid, increase fail count and store url
      if(valid == false) {
        fails++;
        badUrlsGood[k] = url;
        k++;
      }
	  if (valid2 == false) {
		  fails++;
		  badUrlsPoor[r] = urlf;
		  r++;
		  
	  }
    }
    // print results
    System.out.println("\nNumber of Bugs: " + fails + "\n");
    System.out.println("\nBad URLs: \n");
    for (int j = 0; j < badUrlsGood.runs; j++) {
      if(badUrlsGood[j] != null){
    	System.out.println(badUrlsGood[j] + "\n");
      }
    } 
	System.out.println("\nPoor URLs that failed: \n");
    for (int s = 0; s < badUrlsPoor.runs; s++) {
      if(badUrlsGood[s] != null){
    	System.out.println(badUrlsPoor[s] + "\n");
      }
    } 
  }

}
