import React from 'react';
import {SiGithub} from 'react-icons/si';
import {BsLinkedin, BsGithub, BsFacebook, BsYoutube} from 'react-icons/bs'

const Footer = () => (
    <div className="footer">
      <h4>Muhammad Abd-Elsattar</h4>
      <div className="social-links">
        <h4><a href='https://www.linkedin.com/in/muhammadalsattar/' target='_blank'><BsLinkedin/></a></h4>
        <h4><a href='https://github.com/muhammadalsattar/' target='_blank'><BsGithub/></a></h4>
        <h4><a href='https://www.facebook.com/mmuhhammaddd/' target='_blank'><BsFacebook/></a></h4>
        <h4><a href='https://www.youtube.com/channel/UCEQ9gXGizfEQdM0hxUD3XLg' target='_blank'><BsYoutube/></a></h4>
      </div>
    </div>
)

export default Footer;