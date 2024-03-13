package rtc.volcengine.apiexample.examples.ThirdBeauty.byteBeauty;

public class EffectNode {
    public enum EffectType {
        beauty, filter, sticker, virtualBackground;
    }

    public String name; // UI上展示的名称
    public String key; // 素材的键值，区分具体美颜效果、美形效果、滤镜、贴纸

    public EffectType type;

    public String path;

    public float value; // 美颜、美形、滤镜的强度
    public boolean selected; // 是否选中

    public EffectNode(String name, String key, EffectType type) {
        this.name = name;
        this.key = key;
        this.type = type;
    }

    public EffectNode(String name, String key, EffectType type, String path) {
        this(name, key, type);
        this.path = path;
    }

    @Override
    public String toString() {
        return "EffectNode{" +
                "name='" + name + '\'' +
                ", key='" + key + '\'' +
                ", value=" + value +
                ", selected=" + selected +
                '}';
    }

    /**
     * 美颜效果发生变化时的回调
     */
    public interface EffectNodeCallback {

        /**
         * 当美颜被点击时回调
         * @param effectNode 具体的美颜效果，selected字段标识的是选中还是未选中
         */
        void onEffectClicked(EffectNode effectNode);

        /**
         * 当美颜强度改变时回调
         * @param effectNode 具体的美颜效果，value字段表示强度
         */
        void onEffectValueChanged(EffectNode effectNode);
    }
}
