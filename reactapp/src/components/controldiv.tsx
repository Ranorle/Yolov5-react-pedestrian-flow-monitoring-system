import React, { useState, useEffect } from 'react';
import { Button ,notification} from 'antd';
import axios from 'axios';
import '../pages/mainpage.css';
import { InputNumber } from 'antd';
import { Select } from 'antd';
import httpinfo from './http';


// Filter `option.label` match the user type `input`
const filterOption = (input: string, option?: { label: string; value: string }) =>
  (option?.label ?? '').toLowerCase().includes(input.toLowerCase());

const Controdiv: React.FC = () => {
  const [startStatus, setStartStatus] = useState<boolean>(true);
  const [detectScore, setDetectscore] = useState<number | null>(0);
  const [debounceparam, setdebounceparam] = useState<number | null>(0);
  const [detecthing, setDetecthing] = useState<string>('person');
  let initinfo= {
    data:{
      detectscore:0,
      detectobject:'person',
        debounce:0,

  }
}
  let ifcanchange =true;
  if(initinfo.data){
    if(initinfo.data.detectscore===detectScore&&initinfo.data.detectobject===detecthing&&initinfo.data.debounce===debounceparam){
    ifcanchange=false;
  }}
  useEffect(() => {
    const fetchInitInfo = async () => {
      try {
        // 发送 GET 请求到 127.0.0.1:8081/init
        const response = await axios.get(httpinfo+'/init');
        // 设置初始启动状态
        initinfo = response.data;
        setStartStatus(!response.data.pauseparam); // 如果 pauseparam 为 false，则启动状态为 true
        setDetectscore(response.data.detectscore);
        setdebounceparam(response.data.debounce);
        setDetecthing(response.data.detectobject);
      } catch (error) {
        console.error('Error fetching init info:', error);
      }
    };

    // 在组件挂载时获取初始化信息
    fetchInitInfo();
  }, []); // 依赖项为空数组，表示仅在组件挂载时运行一次

  const [api, contextHolder] = notification.useNotification();

  const openNotification = (message:string,description:string) => {
    api.open({
      message: message,
      description:description,
      duration: 3,
    });
  };

  const sendControlRequest = async (action: string) => {
    try {
      // 构造 x-www-form-urlencoded 格式的请求参数
      const params = new URLSearchParams();
      params.append('action', action);

      // 发送 POST 请求到 127.0.0.1:8081/control
      await axios.post(httpinfo+'/control', params, {
        headers: {
          'Content-Type': 'application/x-www-form-urlencoded',
        },
      });

      // 更新状态
      setStartStatus(action === 'start');
      openNotification('Success', '检测状态修改成功');
    } catch (error) {
      console.error('Error sending control request:', error);
      openNotification('Error', '检测状态修改失败');

    }
  };

  const sendDownloadRequest = async () => {
    const link = document.createElement('a');
    // 设置链接的 href 属性为下载文件的 URL
    link.href = httpinfo + '/logdownload';
    // 设置下载的文件名，你可以根据需要自定义
    link.download = 'result.log';
    // 将 <a> 标签添加到 DOM 中
    document.body.appendChild(link);
    // 触发点击事件，浏览器会自动下载文件
    link.click();
    // 移除 <a> 标签，清理 DOM
    document.body.removeChild(link);
  };
  const sendChangeRequest = async () => {
    try {
      // 构造 x-www-form-urlencoded 格式的请求参数
      const params = new URLSearchParams();
      params.append('detectscore', String(detectScore));
      params.append('detectobject', detecthing);
      params.append('debounce', String(debounceparam));


      // 发送 POST 请求到 127.0.0.1:8081/change
      await axios.post(httpinfo+'/change', params, {
        headers: {
          'Content-Type': 'application/x-www-form-urlencoded',
        },
      });
      openNotification('Success', '修改成功');
    } catch (error) {
      console.error('Error sending control request:', error);
      openNotification('Error', '修改失败');

    }
  };

  return (
    <div className='Controdiv'>
          {contextHolder}
      <div className='ButtonDiv'>
        <Button
          size='large'
          type="primary"
          disabled={startStatus}
          onClick={() => sendControlRequest('start')}
        >
          开始检测
        </Button>
        <Button
          size='large'
          disabled={!startStatus}
          onClick={() => sendControlRequest('stop')}
        >
          暂停检测
        </Button>
        <Button
          size='large'
          onClick={() => sendDownloadRequest()}
        >
          下载日志
        </Button>
      </div>
      <div className='Formdiv'>
        <div className='inputdiv'><p className='inputp'>分数阈值: </p>{<InputNumber min={0} max={1} style={{ width: 180 }} value={detectScore} onChange={(value) => {
          setDetectscore(value);
        }} />}</div>
        <div className='inputdiv'><p className='inputp'>消抖阈值: </p>{<InputNumber min={0} max={99} style={{ width: 180 }} value={debounceparam} onChange={(value) => {
          setdebounceparam(value);
        }} />}</div>
        <div className='inputdiv'><p className='inputp'>检测物体: </p><Select
          showSearch
          placeholder="Select a object"
          optionFilterProp="children"
          onChange={(value) => { setDetecthing(value) }}
          style={{ width: 180 }}
          filterOption={filterOption}
          value={detecthing}
          options={[
            {
              value: 'person',
              label: 'person',
            },
            {
              value: 'car',
              label: 'car',
            },
            {
              value: 'airplane',
              label: 'airplane',
            },
          ]}
        /></div>
        <div className='ButtonDiv'>
        <Button
          size='large'
          type="primary"
          onClick={() => {
            sendChangeRequest();
          }}
        >
          确认修改
        </Button>
        <Button
          size='large'
          disabled={!ifcanchange}
          onClick={() => { 
          setDetectscore(initinfo.data.detectscore)
          setDetecthing(initinfo.data.detectobject)
          setdebounceparam(initinfo.data.debounce)
          }}
        >
          回到初始值
        </Button>
        </div>
        Yolo5人流量检测系统 made by @DSY
      </div>
    </div>
  );
};

export default Controdiv;
