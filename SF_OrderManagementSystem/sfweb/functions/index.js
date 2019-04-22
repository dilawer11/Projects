const functions = require('firebase-functions');

// exports.helloWorld = functions.https.onRequest((request, response) => {
//  response.send("Hello from Firebase!");
// });
const admin =  require('firebase-admin');
const nodemailer = require('nodemailer')
admin.initializeApp()

exports.sendMail = functions.https.onCall((data,context)=>{
    const emailBody = data.body
    const to = data.to
    const from = data.from
    var transporter = nodemailer.createTransport({
    service: 'gmail',
    secure: false,
    port: 587,
    auth: {
        user: 'noreply.surgicalfibre@gmail.com',
        pass: 'Temp@123'
    },
    tls : {
        rejectUnauthorised: false
    }
    });

    var mailOptions = {
        from: data.from,
        to: data.to,
        subject: 'Query',
        text: emailBody
    };
    transporter.sendMail(mailOptions)
    return{
        result : 'done'
    }
})
