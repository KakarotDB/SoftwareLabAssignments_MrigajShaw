/**
 * A small helper JS file that adds functionality to the Print button.
 * 
 * VIVA POINTS:
 * - window.print() is a method that opens the browser's native print dialog.
 * - We attach an event listener to the button after it has been created by document.write().
 */

// Since the button is created via document.write() before this script runs, it is available in the DOM.
document.addEventListener("DOMContentLoaded", function() {
    const printBtn = document.getElementById("printBtn");
    if (printBtn) {
        printBtn.addEventListener("click", function() {
            // Opens the print dialog
            window.print();
        });
    }
});
