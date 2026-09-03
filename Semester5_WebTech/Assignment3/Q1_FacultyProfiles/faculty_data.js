/**
 * faculty_data.js
 * 
 * VIVA-READY EXPLANATION: How JSON data storage works in JavaScript
 * JSON (JavaScript Object Notation) is a lightweight format for storing and transporting data.
 * While this is technically an array of JavaScript objects, it follows JSON-like structure.
 * Storing data this way mimics a real-world scenario where a frontend receives JSON from a REST API.
 * It allows us to easily iterate over the data using methods like .map(), .filter(), and .find().
 */

const facultyData = [
    {
        id: "abhik_mukherjee",
        name: "Dr. Abhik Mukherjee",
        title: "Dr.",
        firstName: "Abhik",
        lastName: "Mukherjee",
        email: "abhik@cs.iiests.ac.in",
        qualification: ["Ph.D. (BESU Shibpur, 2003)", "M.Tech Control Systems (Jadavpur University, 1994)", "B.E. Electronics & Telecom (Jadavpur University, 1991)"],
        research: ["Guidance", "Control & Target Tracking", "Mobile Computing", "Soft Computing"],
        subjects: ["Control Systems", "Embedded Systems", "Computer Networks"],
        designation: "Professor",
        imageFile: "images/abhik_mukherjee.jpg"
    },
    {
        id: "amit_kumar_das",
        name: "Dr. Amit Kumar Das",
        title: "Dr.",
        firstName: "Amit Kumar",
        lastName: "Das",
        email: "amit@cs.iiests.ac.in",
        qualification: ["Ph.D. Computer Science"],
        research: ["Document Image Processing", "Image Segmentation", "Pattern Recognition"],
        subjects: ["Digital Image Processing", "Pattern Recognition", "Computer Vision"],
        designation: "Professor",
        imageFile: "images/amit_kumar_das.jpg"
    },
    {
        id: "apurba_sarkar",
        name: "Dr. Apurba Sarkar",
        title: "Dr.",
        firstName: "Apurba",
        lastName: "Sarkar",
        email: "apurba@cs.iiests.ac.in",
        qualification: ["Ph.D. Computer Science"],
        research: ["Digital Geometry", "Combinatorial Geometry", "Discrete Geometry", "Computational Geometry", "Image Processing", "Shape Analysis", "Text Summarization"],
        subjects: ["Discrete Mathematics", "Computational Geometry", "Algorithms"],
        designation: "Associate Professor",
        imageFile: "images/apurba_sarkar.jpg"
    },
    {
        id: "ashish_kumar_layek",
        name: "Dr. Ashish Kumar Layek",
        title: "Dr.",
        firstName: "Ashish Kumar",
        lastName: "Layek",
        email: "ashish@cs.iiests.ac.in",
        qualification: ["Ph.D.", "M.E."],
        research: ["Wireless Telecommunication", "Networking", "Pattern Recognition", "Computer Vision", "Digital Image Processing"],
        subjects: ["Wireless Communication", "Computer Networks", "Digital Image Processing"],
        designation: "Assistant Professor",
        imageFile: "images/ashish_kumar_layek.jpg"
    },
    {
        id: "asit_kumar_das",
        name: "Dr. Asit Kumar Das",
        title: "Dr.",
        firstName: "Asit Kumar",
        lastName: "Das",
        email: "akdas@cs.iiests.ac.in",
        qualification: ["Ph.D. (BESU 2011)", "M.Tech (2002)", "B.Tech (1996) - Computer Science, Calcutta University"],
        research: ["Data Mining", "Pattern Recognition", "Social Networks", "Bioinformatics", "Machine Learning", "Soft Computing", "Text/Audio/Video Analysis"],
        subjects: ["Data Mining", "Machine Learning", "Soft Computing"],
        designation: "Professor",
        imageFile: "images/asit_kumar_das.jpg"
    },
    {
        id: "biplab_kumar_sikdar",
        name: "Dr. Biplab Kumar Sikdar",
        title: "Dr.",
        firstName: "Biplab Kumar",
        lastName: "Sikdar",
        email: "biplab@cs.iiests.ac.in",
        qualification: ["Ph.D. (BESU 2003)", "M.Tech CSE (Calcutta University 1990)", "B.Tech CSE (Calcutta University 1988)", "B.Sc Physics (Presidency College 1985)"],
        research: ["Cellular Automata", "Computer Architecture", "Quantum Computing"],
        subjects: ["Computer Architecture", "Theory of Computation", "Quantum Computing"],
        designation: "Professor",
        imageFile: "images/biplab_kumar_sikdar.jpg"
    },
    {
        id: "jaya_sil",
        name: "Dr. Jaya Sil",
        title: "Dr.",
        firstName: "Jaya",
        lastName: "Sil",
        email: "js@cs.iiests.ac.in",
        qualification: ["Ph.D. CS - AI & Soft Computing (1996)", "M.E. CSE (1986)", "B.E. Electronics & Telecom (1984)"],
        research: ["Image Processing", "Computer Vision", "Machine Learning", "Bio-Informatics", "Soft Computing", "Natural Language Processing"],
        subjects: ["Artificial Intelligence", "Machine Learning", "Natural Language Processing"],
        designation: "Professor",
        imageFile: "images/jaya_sil.jpg"
    },
    {
        id: "malay_kule",
        name: "Dr. Malay Kule",
        title: "Dr.",
        firstName: "Malay",
        lastName: "Kule",
        email: "malay@cs.iiests.ac.in",
        qualification: ["Ph.D. Engineering (IIEST Shibpur)", "M.Tech CSE (Calcutta University)", "B.Tech CSE (Calcutta University)", "B.Sc Physics Honours"],
        research: ["Defect Tolerance", "Nanoscale Circuits Testing", "Cryptology", "Hardware Security", "Social Network Security"],
        subjects: ["Cryptography", "Hardware Security", "VLSI Design"],
        designation: "Professor",
        imageFile: "images/malay_kule.jpg"
    },
    {
        id: "manas_hira",
        name: "Mr. Manas Hira",
        title: "Mr.",
        firstName: "Manas",
        lastName: "Hira",
        email: "manas@cs.iiests.ac.in",
        qualification: ["M.Tech Computer Science"],
        research: ["Circuit Verification using Temporal Logic", "Image Generation and Recognition (Grammatical Approach)"],
        subjects: ["Compiler Design", "Formal Languages", "Automata Theory"],
        designation: "Assistant Professor",
        imageFile: "images/manas_hira.jpg"
    },
    {
        id: "nirnay_ghosh",
        name: "Dr. Nirnay Ghosh",
        title: "Dr.",
        firstName: "Nirnay",
        lastName: "Ghosh",
        email: "nirnay@cs.iiests.ac.in",
        qualification: ["Ph.D. Computer Science"],
        research: ["Information Security", "Network Security", "Mobile Crowdsensing", "Internet of Things (IoT)", "Cloud Computing"],
        subjects: ["Information Security", "Cloud Computing", "IoT"],
        designation: "Assistant Professor",
        imageFile: "images/nirnay_ghosh.jpg"
    },
    {
        id: "samit_biswas",
        name: "Dr. Samit Biswas",
        title: "Dr.",
        firstName: "Samit",
        lastName: "Biswas",
        email: "samit@cs.iiests.ac.in",
        qualification: ["Ph.D. Computer Science"],
        research: ["Digital Image Processing", "Pattern Recognition", "Data Mining", "Natural Language Processing"],
        subjects: ["Image Processing", "Pattern Recognition", "Data Mining"],
        designation: "Associate Professor",
        imageFile: "images/samit_biswas.jpg"
    },
    {
        id: "sekhar_mandal",
        name: "Dr. Sekhar Mandal",
        title: "Dr.",
        firstName: "Sekhar",
        lastName: "Mandal",
        email: "sekhar@cs.iiests.ac.in",
        qualification: ["Ph.D.", "M.Tech Radio Physics & Electronics (Calcutta University)", "B.Tech Radio Physics & Electronics (Calcutta University)"],
        research: ["Computer Vision", "Pattern Recognition", "Image Processing"],
        subjects: ["Computer Vision", "Signal Processing", "Image Processing"],
        designation: "Associate Professor",
        imageFile: "images/sekhar_mandal.jpg"
    },
    {
        id: "sipra_das_bit",
        name: "Dr. Sipra Das Bit",
        title: "Dr.",
        firstName: "Sipra",
        lastName: "Das Bit",
        email: "sb@cs.iiests.ac.in",
        qualification: ["Ph.D. Engineering - CS&E (Jadavpur University 1997)"],
        research: ["Mobile Computing", "Wireless Sensor Networks (WSN)", "Delay Tolerant Networks (DTN)", "Internet of Things (IoT)"],
        subjects: ["Mobile Computing", "Wireless Networks", "IoT"],
        designation: "Professor",
        imageFile: "images/sipra_das_bit.jpg"
    },
    {
        id: "somnath_pal",
        name: "Dr. Somnath Pal",
        title: "Dr.",
        firstName: "Somnath",
        lastName: "Pal",
        email: "sp@cs.iiests.ac.in",
        qualification: ["Ph.D. Computer Science"],
        research: ["Symbolic Logic", "Artificial Intelligence", "Brain & Behavioral Sciences", "Nature Inspired Algorithms"],
        subjects: ["Artificial Intelligence", "Logic Programming", "Nature Inspired Computing"],
        designation: "Associate Professor",
        imageFile: "images/somnath_pal.jpg"
    },
    {
        id: "sulata_mitra",
        name: "Dr. Sulata Mitra",
        title: "Dr.",
        firstName: "Sulata",
        lastName: "Mitra",
        email: "sulata@cs.iiests.ac.in",
        qualification: ["Ph.D. Computer Science"],
        research: ["Mobile Computing", "Ad-hoc Networks", "Multihomed Mobile Networks", "QoS in Cellular Networks"],
        subjects: ["Mobile Communication", "Ad-hoc Networks", "Wireless Technology"],
        designation: "Professor",
        imageFile: "images/sulata_mitra.jpg"
    },
    {
        id: "surajeet_ghosh",
        name: "Dr. Surajeet Ghosh",
        title: "Dr.",
        firstName: "Surajeet",
        lastName: "Ghosh",
        email: "surajeet@cs.iiests.ac.in",
        qualification: ["Ph.D. Computer Science"],
        research: ["Computer Architecture", "Custom Computing", "Computational Architecture for DNA Sequencing", "Network Routing Schemes"],
        subjects: ["Computer Organization", "VLSI Design", "High Performance Computing"],
        designation: "Assistant Professor",
        imageFile: "images/surajeet_ghosh.jpg"
    },
    {
        id: "susanta_chakraborty",
        name: "Dr. Susanta Chakraborty",
        title: "Dr.",
        firstName: "Susanta",
        lastName: "Chakraborty",
        email: "sc@cs.iiests.ac.in",
        qualification: ["Ph.D. Computer Science"],
        research: ["Social Network Analysis", "Machine Learning", "Data Mining", "IoT Security", "Intelligent System Design", "Quantum Computing", "Image Processing"],
        subjects: ["Social Networks", "Machine Learning", "Database Management"],
        designation: "Professor",
        imageFile: "images/susanta_chakraborty.jpg"
    },
    {
        id: "tamal_pal",
        name: "Dr. Tamal Pal",
        title: "Dr.",
        firstName: "Tamal",
        lastName: "Pal",
        email: "tamal@cs.iiests.ac.in",
        qualification: ["Ph.D. Computer Science"],
        research: ["Image Processing", "Wireless Multimedia Sensor Networks"],
        subjects: ["Multimedia Systems", "Wireless Networks", "Image Processing"],
        designation: "Assistant Professor",
        imageFile: "images/tamal_pal.jpg"
    }
];

/**
 * Searches for a faculty member by their exact name.
 * @param {string} name - The full name of the faculty member.
 * @returns {object|null} - The faculty object if found, otherwise null.
 */
function getFacultyByName(name) {
    return facultyData.find(faculty => faculty.name === name) || null;
}
