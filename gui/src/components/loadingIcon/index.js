import React from 'react';
import './loadingIcon.scss';

// Generic loading component (https://loading.io/css/)
const LoadingIcon = (props) => {
  return (
    <div className="lds-ellipsis"><div /><div /><div /><div /></div>
  );
};

export default LoadingIcon;
