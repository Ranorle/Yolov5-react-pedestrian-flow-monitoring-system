import React, { useState, useEffect } from 'react';
import '../pages/mainpage.css';
import { Spin } from 'antd';
import httpinfo from './http';

const Videorect: React.FC = () => {
  const [imageSrc, setImageSrc] = useState<string>(httpinfo+'/video');
  let label1=0;
  useEffect(() => {
    const updateImage = async () => {
      // 使用当前时间戳作为查询参数，以确保每次请求都是新的
      const timestamp = new Date().getTime();
      const newImageSrc = httpinfo+`/video?timestamp=${timestamp}`;

      try {
        // 尝试加载新图片
        await new Promise((resolve, reject) => {
          const img = new Image();
          img.onload = resolve;
          img.onerror = reject;
          img.src = newImageSrc;
        });

        // 成功加载新图片后更新显示的图片
        setImageSrc(newImageSrc);
        label1=1;
      } catch (error) {
        label1=0;
        console.error('Error loading image:', error);
      }
    };

    // 每隔一段时间调用updateImage函数，实现不停获取图片
    const intervalId = setInterval(updateImage, 1000 / 30); // 24fps的间隔，你可以根据需要调整

    // 组件卸载时清除定时器
    return () => clearInterval(intervalId);
  }, [imageSrc]); // 添加依赖项，确保在这两个值变化时重新执行effect

  return (
    <div className='Videorect'>
      {imageSrc===httpinfo+'video' ? <Spin size="large"/>:<img src={imageSrc} alt="Stream" />}
    </div>
  );
};

export default Videorect;
