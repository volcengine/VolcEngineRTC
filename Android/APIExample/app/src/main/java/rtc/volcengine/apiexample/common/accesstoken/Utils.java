package rtc.volcengine.apiexample.common.accesstoken;

import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;
import java.util.Date;
import java.util.zip.CRC32;

public class Utils {
    public static final long HMAC_SHA256_LENGTH = 32;
    public static final int VERSION_LENGTH = 3;
    public static final int APP_ID_LENGTH = 24;

    public static byte[] hmacSign(String keyString, byte[] msg) throws InvalidKeyException, NoSuchAlgorithmException {
        SecretKeySpec keySpec = new SecretKeySpec(keyString.getBytes(), "HmacSHA256");
        Mac mac = Mac.getInstance("HmacSHA256");
        mac.init(keySpec);
        return mac.doFinal(msg);
    }

    public static String base64Encode(byte[] data) {
        byte[] encodedBytes = Base64.getEncoder().encode(data);
        return new String(encodedBytes);
    }

    public static byte[] base64Decode(String data) {
        return Base64.getDecoder().decode(data.getBytes());
    }

    public static int getTimestamp() {
        return (int)((new Date().getTime())/1000);
    }

    public static int randomInt() {
        return new SecureRandom().nextInt();
    }

}