# Faculty Images Directory

This directory is intended to store the photos for the IIEST CST Faculty Profile System.

## Image Naming Convention
For the images to link up correctly with the provided JavaScript data, they must be named using the format:
`firstname_lastname.jpg` (all lowercase, using underscores instead of spaces).

For example:
- Dr. Abhik Mukherjee -> `abhik_mukherjee.jpg`
- Dr. Asit Kumar Das -> `asit_kumar_das.jpg`

## Where to get images
The official IIEST website uses a specific URL pattern for faculty photos:
`https://www.iiests.ac.in/assets/faculty/[id].jpg`

You can download the images from the official site and place them in this folder following the naming convention above.

## Fallback
If an image is not found (e.g., you haven't added it yet), the `onerror` event in the `profile.html` `<img>` tag will catch the error and automatically replace the broken image with a styled placeholder displaying the faculty member's initials.
