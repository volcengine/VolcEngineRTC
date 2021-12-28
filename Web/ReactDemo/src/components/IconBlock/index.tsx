import React from 'react';

import IIconBlockProps from './type';
import SC from './style';

const IconBlock: React.FC<IIconBlockProps> = (props) => {
  const {children, ...restProps} = props;
  return <SC.IconBlockWrapper {...restProps}>{children}</SC.IconBlockWrapper>;
};

export default IconBlock;
