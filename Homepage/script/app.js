// handling scrolling to top window
document.querySelector("#scroll-top").addEventListener("click", event => {
    window.scrollTo({
        top: 0,
        left: 0,
        behavior: "smooth"
    })
})