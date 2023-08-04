import React from 'react';
import ControlModules from './controlItem';
import SystemModules from './systemItms';

import SC from './style';
import { IControlBarProps } from './type';


const ControlBar: React.FC<IControlBarProps> =(props)=>{

  const { moduleConf = [], systemConf=[], RClient } = props;

  const attchModules = () => {
    return (
      <>
        {moduleConf.map((item, index) => {
          const {visible = true, moduleProps = {}} = item || {};
          const Comp = ControlModules[item.moduleName];
          return visible && Comp ? (
            <Comp RClient={RClient} {...moduleProps} key={index}/>
          ) : null;
        })}
      </>
    );
  };

  const attchSystem = () => {
    return (
      <>
        {systemConf.map((item, index) => {
          const {visible = true, moduleProps = {}} = item || {};
          const Comp = SystemModules[item.moduleName];
          return visible && Comp ? (
            <Comp RClient={RClient} {...moduleProps} key={index}/>
          ) : null;
        })}
      </>
    );
  };

  return (
    <SC.ControlBarWrapper>
      <SC.ControlModulesWrapper>{attchModules()}</SC.ControlModulesWrapper>
      <SC.SystemModulesWrapper>
        {attchSystem()}
      </SC.SystemModulesWrapper>
    </SC.ControlBarWrapper>
  );
};

export default ControlBar;