

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
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
	   assertFalse(urlValidator.isValid("http://www.google.com/wrong//path"));
	   
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
   

   
   
}
