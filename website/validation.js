const form = document.getElementById('form');
const email = document.getElementById('email');
const password = document.getElementById('password');
const rePassword = document.getElementById('re-password');
const message = document.getElementById('error-message');

let allInputs = [email, password, rePassword].filter(input => input !== null)

form.addEventListener('submit', e => {
    let errors = []
    let str = '';
    if (rePassword !== null) {
        errors = validationSignUp(email.value, password.value, rePassword.value)
    } else {
        errors = validationLogin(email.value, password.value)
    }

    if (errors.length > 0) {
        errors.forEach(element => {
            str = str + element + "<br>";
        })
        message.innerHTML = str;
        e.preventDefault();
    }

    
});

const validationSignUp = (emailInput, passwordInput, rePasswordInput) => {
    let errors = [];
    if (emailInput < 1) {
        errors.push("Bad email");
        email.classList.add('incorrect');
    }
    if (passwordInput < 1) {
        errors.push("Bad Password");
        password.classList.add('incorrect');
    }
    if (rePasswordInput < 1) {
        errors.push("Bad rePassword");
        rePassword.classList.add('incorrect');
    }
    return errors;
}

const validationLogin = (emailInput, passwordInput) => {
    let errors = [];
    if (emailInput < 1) {
        errors.push("Bad email");
        email.classList.add('incorrect');
    }
    if (passwordInput < 1) {
        errors.push("Bad Password");
        password.classList.add('incorrect');
    }
    return errors;
}

allInputs.forEach(input => {
    input.addEventListener('input', () =>{
        if(input.classList.contains('incorrect')) {
            input.classList.remove('incorrect');
        }
    })
})