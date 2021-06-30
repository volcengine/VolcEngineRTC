#include "utils/json_util.h"
#include <random>

#define kBIN_PLACE_HOLDER "_placeholder"

namespace {

void TransferSioBoolMessage(sio::bool_message const &msg, Json::Value &val) {
    val = msg.get_bool();
}

void TransferSioNullMessage(Json::Value &val) {
    val = Json::Value::null;
}

void TransferSioIntMessage(sio::int_message const &msg, Json::Value &val) {
    val = (Json::Value::Int64)msg.get_int();
}

void TransferSioDoubleMessage(sio::double_message const &msg, Json::Value &val) {
    val = msg.get_double();
}

void TransferSioStringMessage(sio::string_message const &msg, Json::Value &val) {
    val = msg.get_string().data();
}

void TransferSioBinaryMessage(sio::binary_message const &msg,
        Json::Value &val,
        std::vector<std::shared_ptr<const std::string> > &buffers) {
    val[kBIN_PLACE_HOLDER] = true;
    val["num"] = (Json::Value::Int64) buffers.size();
    //TODO tangxiangjun, check why buffer not add to json.
    //FIXME can not avoid binary copy here.
    std::shared_ptr<std::string> write_buffer = std::make_shared<std::string>();
    write_buffer->reserve(msg.get_binary()->size() + 1);
    char frame_char = 4;
    write_buffer->append(&frame_char, 1);
    write_buffer->append(*(msg.get_binary()));
    buffers.push_back(write_buffer);
}

void TransferSioArrayMessage(sio::array_message const &msg,
        Json::Value &val,
        std::vector<std::shared_ptr<const std::string> > &buffers) {
    for (std::vector<sio::message::ptr>::const_iterator it = msg.get_vector().begin(); it != msg.get_vector().end();
         ++it) {
        Json::Value childValue;
        TransferSioMessageToJson(*(*it), childValue, buffers);
        val.append(childValue);
    }
}

void TransferSioObjectMessage(sio::object_message const &msg,
        Json::Value &val,
        std::vector<std::shared_ptr<const std::string> > &buffers) {
    for (std::map<std::string, sio::message::ptr>::const_iterator it = msg.get_map().begin(); it != msg.get_map().end();
         ++it) {
        Json::Value value;
        TransferSioMessageToJson(*(it->second), value, buffers);
        val[it->first.data()] = value;
    }
}

static void TransferJsonNode(const std::string &name, const Json::Value &val, sio::object_message *sioNode) {
    if (val.isString()) {
        sioNode->insert(name, val.asString());
    } else if (val.isBool()) {
        sioNode->insert(name, sio::bool_message::create(val.asBool()));
    } else if (val.isInt()) {
        sioNode->insert(name, sio::int_message::create(val.asInt()));
    } else if (val.isUInt()) {
        sioNode->insert(name, sio::int_message::create(val.asUInt()));
    } else if (val.isDouble()) {
        sioNode->insert(name, sio::double_message::create(val.asDouble()));
    } else if (val.isInt64()) {
        sioNode->insert(name, sio::int_message::create(val.asInt64()));
    } else if (val.isObject()) {
        sio::message::ptr message;
        TransferJsonToSioMessage(val, message);
        sioNode->insert(name, message);
    } else if (val.isArray()) {
        sio::message::ptr message1 = sio::array_message::create();
        sio::array_message *temp2 = (sio::array_message *) message1.get();
        for (unsigned int i = 0; i < val.size(); ++i) {
            const Json::Value &item = val[i];
            if (item.isString()) {
                temp2->push(item.asString());
            } else if (item.isBool()) {
                temp2->push(sio::bool_message::create(item.asBool()));
            } else if (item.isDouble()) {
                // ���������ų����и�����
                temp2->push(sio::double_message::create(item.asDouble()));
            } else if (item.isInt64()) {
                // ������������ֶ��ǷǸ������ˣ�����ͳһ����int����
                temp2->push(sio::int_message::create(item.asInt64()));
            } else if (item.isObject()) {
                sio::message::ptr message1;
                TransferJsonToSioMessage(item, message1);
                temp2->push(message1);
            }
        }
        sioNode->insert(name, message1);
    }
}
}

void TransferSioMessageToJson(sio::message const &msg, Json::Value &val,
        std::vector<std::shared_ptr<const std::string> > &buffers) {
    const sio::message *msg_ptr = &msg;
    switch (msg.get_flag()) {
        case sio::message::flag_integer: {
            TransferSioIntMessage(*(static_cast<const sio::int_message *>(msg_ptr)), val);
            break;
        }
        case sio::message::flag_double: {
            TransferSioDoubleMessage(*(static_cast<const sio::double_message *>(msg_ptr)), val);
            break;
        }
        case sio::message::flag_string: {
            TransferSioStringMessage(*(static_cast<const sio::string_message *>(msg_ptr)), val);
            break;
        }
        case sio::message::flag_boolean: {
            TransferSioBoolMessage(*(static_cast<const sio::bool_message *>(msg_ptr)), val);
            break;
        }
        case sio::message::flag_null: {
            TransferSioNullMessage(val);
            break;
        }
        case sio::message::flag_binary: {
            TransferSioBinaryMessage(*(static_cast<const sio::binary_message *>(msg_ptr)), val, buffers);
            break;
        }
        case sio::message::flag_array: {
            TransferSioArrayMessage(*(static_cast<const sio::array_message *>(msg_ptr)), val, buffers);
            break;
        }
        case sio::message::flag_object: {
            TransferSioObjectMessage(*(static_cast<const sio::object_message *>(msg_ptr)), val, buffers);
            break;
        }
        default: break;
    }
}

void TransferJsonToSioMessage(const Json::Value &val, sio::message::ptr &message) {
    message = sio::object_message::create();
    sio::object_message *sioNode = (sio::object_message *) message.get();
    for (Json::Value::const_iterator itr = val.begin();
         itr != val.end(); ++itr) {
        TransferJsonNode(itr.key().asString(), *itr, sioNode);
    }
}
