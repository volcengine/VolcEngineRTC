import styled from 'styled-components';
import IProps from './type';

const DividerWrapper = styled.div`
  width: ${(props: IProps) => props.width || 24}px;
  height: ${(props: IProps) => props.height || 24}px;
  background: ${(props: IProps) => props.bgColor || '#E5E5E5'};
  margin-left: ${(props: IProps) => props.marginL || 20}px;
`;

export default DividerWrapper;