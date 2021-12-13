import React from "react";

export default function SkillsCard(props) {
    return(
        <div className="col-6 col-md-4  mb-3">
              <div className="card">
                <div className="card-body">
                  <h4 className="card-title"><mark>{props.title}</mark></h4>
                  <small className="card-text"><mark>{props.level}</mark></small>
                </div>
              </div>
            </div>
    )
}