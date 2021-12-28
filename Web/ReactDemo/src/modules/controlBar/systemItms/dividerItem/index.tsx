import React from 'react';
import IDividerProps from './type';
import DividerWrapper from './style';

const DividerItem: React.FC<IDividerProps> = (props) => {
  return (
    <DividerWrapper {...props} />
  );
};

export default DividerItem;