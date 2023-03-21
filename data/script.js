let fnuuy = document.getElementById("fnuuy");
let hi = document.getElementById("hi");
let led = document.getElementById("led_button");

fnuuy.onclick = async () => {
  fnuuy.classList.add("button2");

  fetch("hi")
    .then((res) => res.json())
    .then((data) => {
      console.log(data);
      hi.innerHTML = data.message;
    });
};

async function getLedState() {
  return fetch("led")
    .then((res) => res.json())
    .then((data) => data.led_state);
}

async function setLedButton() {
  if (await getLedState()) {
    led.innerHTML = "LED off";
    led.classList.remove("button2");
  } else {
    led.innerHTML = "LED on";
    led.classList.add("button2");
  }
}

setLedButton();

led.onclick = async () => {
  fetch("led", {
    method: "POST",
    headers: {
      "Content-Type": "text/plain",
    },
    body: await getLedState() ? "off" : "on",
  });
  setLedButton();
};
