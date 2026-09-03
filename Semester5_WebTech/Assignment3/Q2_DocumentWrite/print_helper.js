document.addEventListener("DOMContentLoaded", function() {
    const printBtn = document.getElementById("printBtn");
    if (printBtn) {
        printBtn.addEventListener("click", function() {
            // Opens the print dialog
            window.print();
        });
    }
});
