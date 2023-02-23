import React from 'react';
import RtcClient from './rtc-client';

interface IProps {
  onRef: (ref: any) => void;
  config: any;
  streamOptions: any;
  handleUserPublishStream: any;
  handleUserUnpublishStream: any;
  handleUserStartVideoCapture: any;
  handleUserStopVideoCapture: any;
  handleUserJoin: any;
  handleUserLeave: any;
  handleEventError: any;
}

export default class RtcComponent extends React.Component<IProps, any> {
  rtc: any;
  constructor(props: IProps) {
    super(props);
    this.rtc = new RtcClient(props);
  }
  componentDidMount() {
    this.props.onRef(this.rtc);
  }
  render() {
    return <></>;
  }
}
