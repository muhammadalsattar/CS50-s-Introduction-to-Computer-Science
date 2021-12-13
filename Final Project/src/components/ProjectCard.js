import React from "react";
import { BiLinkExternal } from "react-icons/bi";

export default function ProjectCard(props) {
    return(
        <div className="col-sm-6 mb-3">
              <div className="card">
                <div className="card-body">
                  <h3 className="card-title"><mark>{props.name}</mark></h3>
                  <p className="card-text"><mark>{props.details}</mark></p>
                </div>
                <div className="card-footer">
                  <small><mark>{props.tools}</mark></small>
                </div>
              </div>
        </div>
    )
}