import firebase from 'firebase/app'
import firestore from 'firebase/firestore'
  // Initialize Firebase
  var config = {
    apiKey: "AIzaSyCVTzHZZS8UIYi55qg9vaWrm2w5dK1o8vk",
    authDomain: "surgicalfibre-web.firebaseapp.com",
    databaseURL: "https://surgicalfibre-web.firebaseio.com",
    projectId: "surgicalfibre-web",
    storageBucket: "surgicalfibre-web.appspot.com",
    messagingSenderId: "726442448929"
  };
  const firebaseApp = firebase.initializeApp(config);
 

  export default firebaseApp.firestore()