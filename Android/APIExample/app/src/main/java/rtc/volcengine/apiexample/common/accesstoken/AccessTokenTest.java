package rtc.volcengine.apiexample.common.accesstoken;

// cd java/src/main/java/io/rtc && javac *.java
// cd java/src/main/java && java io.rtc.AccessTokenTest
class AccessTokenTest {

    public static void main(String[] args) {
       AccessToken token = new AccessToken("123456781234567812345678", "app key", "new room", "new user id");
       token.ExpireTime(Utils.getTimestamp() + 3600);
       token.AddPrivilege(AccessToken.Privileges.PrivSubscribeStream, 0);
       token.AddPrivilege(AccessToken.Privileges.PrivPublishStream, Utils.getTimestamp() + 3600);


       String s = token.Serialize();
       System.out.println(s);

       System.out.println(token);

       AccessToken t = AccessToken.Parse(s);
       System.out.println(t);

       System.out.println(t.Verify("app key"));

    }
}