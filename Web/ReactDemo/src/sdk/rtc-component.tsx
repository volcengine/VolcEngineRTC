import React from 'react';
import RtcClient from './rtc-client';


interface IProps{
  onRef: (ref: any)=> void;
  config:any;
  streamOptions:any;
  handleStreamAdd:any
  handleStreamRemove:any;
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