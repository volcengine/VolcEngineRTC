import styled from 'styled-components';

const barWidth = 348;

const ControlBarWrapper = styled.div`
  display: flex;
  flex-direction: row;
  justify-content: space-between;
  align-items: center;
  position: fixed;
  left: 50%;
  margin-left: -${barWidth / 2}px;
  z-index: 1000;
  bottom: 40px;
  color: #fff;
  width: ${barWidth}px;
  height: 59px;
  background-color: #36393f;
  border-radius: 69px;
  padding: 0 24px;
`;

const ControlModulesWrapper = styled.div`
  display: flex;
  position: relative;
  position: relative;
  display: flex;
  flex: 2;
  justify-content: space-around;
`;


const SystemModulesWrapper = styled.div`
  display: flex;
  flex: 1;
  margin-left: 10px;
  justify-content: space-between;
`;


const StyledComp = {
  ControlBarWrapper,
  ControlModulesWrapper,
  SystemModulesWrapper,
};

export default StyledComp;