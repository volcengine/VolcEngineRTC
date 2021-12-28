import { ReactEventHandler } from 'react';

export default interface IIconBlockProps {
  size?: number;
  radius?: number;
  shape?: 'circle' | 'square';
  onClick?: ReactEventHandler;
}