<!-- HTML_HELPER const PROGMEM char script_js[] = TO_STRING(

let fnuuy = document.getElementById("fnuuy");
let hi = document.getElementById("hi");
let led = document.getElementById("led_button");

led.innerHTML = "LED off";

fnuuy.onclick = async () => {
  fnuuy.classList.add("button2");

  fetch("hi")
    .then((res) => res.json())
    .then((data) => {
      console.log(data);
      hi.innerHTML = data.message;
    });
};

led.onclick = async () => {
  fetch("led", { method: "POST" })
    .then((res) => res.json())
    .then((data) => {
      console.log(data);
      if (data.led_state) {
        led.innerHTML = "LED off";
        led.classList.remove("button2");
      } else {
        led.innerHTML = "LED on";
        led.classList.add("button2");
      }
    });
};

<!-- );
