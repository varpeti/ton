import Ton.*;

import java.util.Arrays;


class Main 
{
    public static void main(String[] args) 
    {
        try
        {
            //TODO normal Java test
            Ton eq1 = Ton.parsefromFile("../tests/testEQ1.ton");
            String s1 = eq1.toString();

            Ton eq2 = Ton.parsefromFile("../tests/testEQ2.ton");
            String s2 = eq2.toString();
            System.out.println(s1.equals(s2)); // Cos Java HasMap will keep the lines in the same sort.

            Ton eq3 = Ton.parsefromFile("../tests/testEQ3.ton");
            String s3 = eq3.toString();
            System.out.println(!s1.equals(s3));

            Ton test = Ton.parsefromFile("../tests/test.ton");
            Ton ae = test.get("Creature").get("Animal").get("Ground").get("Mammal").get("Anthropoid").get("Human").get("Male").get("Albert Einstein");
            ae.put("Description", "German physicist");
            ae.putAll("Lived", Arrays.asList("1879","1955"));

            System.out.println(ae.get("Description").containsKey("German physicist"));
            System.out.println(test.get("Creature").get("Animal").get("Ground").get("Mammal").get("Anthropoid").get("Human").get("Male").get("Albert Einstein").get("Lived").containsKey("1879"));
            System.out.println(test.get("Creature").get("Animal").get("Ground").get("Mammal").get("Anthropoid").get("Human").get("Male").get("Albert Einstein").get("Lived").containsKey("1955"));

            //System.out.println(test);

        }
        catch (Exception ex)
        {
            ex.printStackTrace(); //TODO ex handling
        }
    }
}