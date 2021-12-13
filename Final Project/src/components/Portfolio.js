import React from 'react';
import Intro from './Intro';
import Education from './Education';
import Skills from './Skills';
import Projects from './Projects';
import Contact from './Contact';
import Footer from './Footer';

class Portfolio extends React.Component{
    componentDidMount(){
        window.addEventListener('scroll', ()=> {
            if (document.querySelector('.education h2').getBoundingClientRect().y < window.innerHeight / 2){
              document.querySelector('.education .row').style.animationPlayState = 'running'
            }
            if (document.querySelector('.projects .row').getBoundingClientRect().y < window.innerHeight / 2){
                document.querySelector('.projects .row').style.animationPlayState = 'running'
            }
            if (document.querySelector('.skills .row').getBoundingClientRect().y < window.innerHeight / 2){
                document.querySelector('.skills .row').style.animationPlayState = 'running'
            }
          })
    }
    render(){
        return(
            <div className="portfolio">
                <Intro/>
                <Education/>
                <Skills/>
                <Projects/>
                <Contact/>
                <Footer/>
            </div>
        )
    }
}

export default Portfolio