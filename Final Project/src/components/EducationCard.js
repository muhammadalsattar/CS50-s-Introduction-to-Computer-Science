import React from 'react'

export default function EducationCard(props) {
    return(
        <div className="col-sm-6 mb-3">
            <div className="card">
            <div className="card-body">
                <h4 className="card-title"><mark>{props.name}</mark></h4>
                <small className="card-text"><mark>{props.college}</mark></small>
            </div>
            </div>
        </div>
    )
}