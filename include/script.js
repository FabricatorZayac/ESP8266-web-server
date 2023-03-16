<!-- HTML_HELPER String main_js = TO_STRING(

let fnuuy = document.getElementById("fnuuy");
let hi = document.getElementById("hi");

fnuuy.onclick = async () => {
  fnuuy.classList.add("button2");

  fetch("http://$(LOCAL_IP)/hi")
    .then((res) => res.json())
    .then((data) => {
      console.log(data);
      hi.innerHTML = data.message;
    });
}

<!-- );
