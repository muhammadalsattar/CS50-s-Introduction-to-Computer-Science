import React from 'react'
import emailjs from 'emailjs-com';
class Contact extends React.Component {
  
  sendMail = (e) => {
    // Sending the email
    e.preventDefault();
    emailjs.sendForm('service_ttc7wh9', 'template_nr72snt', e.target, 'user_vJ148TvsCvpdl2zU3QhPt')

    // Wiping form fields value
    e.target.username.value = ''
    e.target.useremail.value = ''
    e.target.message.value = ''

    window.scrollTo({
      top: document.querySelector('.alert-light').getBoundingClientRect().top,
      left: 0,
      behavior: 'smooth'
    });
    document.querySelector('.alert-light').style.display = 'inline-block'
  }

  render(){
    return (
      <div className="section contact">
          <h2>Contact</h2>
          <form className="contact-form" onSubmit={this.sendMail}>
            <div className="form-floating mb-3">
              <textarea className="form-control rounded-0" name="message" placeholder="Message" id="floatingTextarea"></textarea>
              <label htmlFor="floatingTextarea">Message</label>
            </div>
            <div className="contact-inline">
              <div className="form-floating">
                <input autoComplete="off" type="text" className="form-control rounded-0" name="username" id="floatingInput" placeholder="Fullname"></input>
                <label htmlFor="floatingInput">Full Name</label>
              </div>
              <div className="form-floating">
                <input type="email" autoComplete="off" className="form-control rounded-0" name="useremail" id="floatingPassword" placeholder="Email"></input>
                <label htmlFor="floatingPassword">Email Address</label>
              </div>
              <button type="submit" className="btn btn-light rounded-0">Submit</button>
            </div>
          </form>
        </div>
    )
  }
}

export default Contact;