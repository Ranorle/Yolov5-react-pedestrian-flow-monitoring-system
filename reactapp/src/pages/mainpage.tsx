import React, { useState } from 'react';
import './mainpage.css'
import Videorect from '../components/videorect';
import Controdiv from '../components/controldiv';

const Mainpage: React.FC = () => {
  return <div className='MainPage'>
  <div className='centerdiv'>
    <Videorect/>
    <Controdiv/>
  </div>
  </div>;
};

export default Mainpage;