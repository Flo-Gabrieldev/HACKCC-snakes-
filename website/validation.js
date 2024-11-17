const form = document.getElementById('form');
const email = document.getElementById('email');
const password = document.getElementById('password');
const rePassword = document.getElementById('re-password');
const message = document.getElementById('error-message');

let allInputs = [email, password, rePassword].filter(input => input !== null)

form.addEventListener('submit', e => {
    let errors = []
    errors = validation(email.value, password.value, rePassword.value)
    if (errors.length > 0) {
        message.innerHTML = errors;
        e.preventDefault();
    }

    
});

const validation = (emailInput, passwordInput, rePasswordInput) => {
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

allInputs.forEach(input => {
    input.addEventListener('input', () =>{
        if(input.classList.contains('incorrect')) {
            input.classList.remove('incorrect');
        }
    })
})