/**
 * Copyright 2024 Beijing Volcano Engine Technology Co., Ltd. All Rights Reserved.
 * SPDX-license-identifier: BSD-3-Clause
 */

import React, { FC, useContext } from 'react';
import styled from 'styled-components';
import { StoreValue } from 'rc-field-form/lib/interface';

import { Input, Button, Form, Modal } from 'antd';
import { Context } from '../../context';
import { setSessionInfo } from '../../utils/index';

type IForm = { roomId: string; userId: string };

const ModalWrapper = styled(Modal)`
  .ant-modal-header {
    border-bottom: none;
    padding: 15px 32px 0px;
  }
  .ant-modal-body {
    padding: 14px 32px 24px;
  }
  .ant-modal-content {
    height: 365px;
    border-radius: 8px;
  }
  .ant-modal-title {
    font-family: PingFang SC;
    font-size: 32px;
    font-style: normal;
    font-weight: 600;
    line-height: 80px;
    text-align: left;
    height: 80px;
  }
  .ant-modal-header {
    border-radius: 6px 6px 0 0;
  }
`;

enum ERROR_TYPES {
  VALID,
  EMPTY_STRING,
  INVALID_CHARACTERS,
}

const messages = {
  userIdErrType: {
    1: '请填写用户Id',
    2: '用户Id输入有误，请重新输入',
  },
  roomIdErrType: {
    1: '请填写房间Id',
    2: '房间Id输入有误，请重新输入',
  },
};

const getLoginFieldRules = (
  value: StoreValue,
  name: 'userId' | 'roomId',
  regRes: boolean
): Promise<void | any> | void => {
  const errorTypeKey = name === 'userId' ? 'userIdErrType' : 'roomIdErrType';

  let result: Promise<Error | void>;

  if (!value || regRes) {
    const _value = !value ? ERROR_TYPES.EMPTY_STRING : ERROR_TYPES.INVALID_CHARACTERS;
    result = Promise.reject(new Error(messages[errorTypeKey][_value]));
  } else {
    result = Promise.resolve();
  }

  return result;
};

const JoinRoom: FC<{ joinRoom: () => void }> = ({ joinRoom }) => {
  const [form] = Form.useForm<IForm>();

  const { setRoomId, setUserId, userId, roomId, joinFailReason } = useContext(Context);

  const onFinish = (value: IForm) => {
    const { roomId, userId } = value;
    setUserId(userId);
    setRoomId(roomId);
    joinRoom();
    setSessionInfo({ roomId, uid: userId });
    window.history.replaceState('', '', `/?userId=${userId}&roomId=${roomId}`);
  };

  return (
    <>
      <ModalWrapper width={390} title="登录" visible={true} closable={false} footer={null} centered>
        <Form form={form} onFinish={onFinish} initialValues={{ userId, roomId }}>
          <Form.Item
            name="roomId"
            rules={[
              {
                required: true,
                validator: (_, value) => {
                  const regRes = !/^[0-9a-zA-Z_\-@.]{1,128}$/.test(value);
                  return getLoginFieldRules(value, 'roomId', regRes);
                },
              },
            ]}
          >
            <Input placeholder="房间ID" size="large" />
          </Form.Item>
          <Form.Item
            name="userId"
            rules={[
              {
                required: true,
                validator: (_, value) => {
                  const regRes = !/^[0-9a-zA-Z_\-@.]{1,128}$/.test(value);
                  return getLoginFieldRules(value, 'userId', regRes);
                },
              },
            ]}
          >
            <Input placeholder="用户ID" size="large" />
          </Form.Item>
          <div style={{ color: 'red'}}>
            {joinFailReason}
          </div>
          <Form.Item>
            <Button
              type="primary"
              htmlType="submit"
              block
              size="large"
              style={{ marginTop: 15, fontWeight: 600 }}
            >
              进入房间
            </Button>
          </Form.Item>
        </Form>
      </ModalWrapper>
    </>
  );
};

export default JoinRoom;
