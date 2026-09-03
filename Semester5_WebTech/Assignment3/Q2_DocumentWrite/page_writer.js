
document.write(`
    <style>
        /* CSS styling embedded via document.write() */
        @import url('https://fonts.googleapis.com/css2?family=Poppins:wght@300;400;600&display=swap');
        
        :root {
            --primary-color: #6a11cb;
            --secondary-color: #2575fc;
            --text-color: #ffffff;
            --bg-color: #1a1a2e;
            --card-bg: rgba(255, 255, 255, 0.1);
        }

        body, html {
            margin: 0;
            padding: 0;
            font-family: 'Poppins', sans-serif;
            background: linear-gradient(135deg, var(--primary-color) 0%, var(--secondary-color) 100%);
            background-attachment: fixed;
            color: var(--text-color);
            min-height: 100vh;
        }

        .container {
            max-width: 1000px;
            margin: 0 auto;
            padding: 20px;
        }

        header {
            text-align: center;
            padding: 50px 0;
            animation: fadeInDown 1s ease-out;
        }

        header h1 {
            font-size: 3em;
            margin-bottom: 10px;
            text-shadow: 2px 2px 4px rgba(0,0,0,0.3);
        }

        header p {
            font-size: 1.2em;
            opacity: 0.9;
        }

        .section {
            background: var(--card-bg);
            border-radius: 15px;
            padding: 30px;
            margin-bottom: 30px;
            backdrop-filter: blur(10px);
            box-shadow: 0 8px 32px 0 rgba(0, 0, 0, 0.37);
            border: 1px solid rgba(255, 255, 255, 0.18);
            animation: fadeInUp 1s ease-out;
        }

        h2 {
            border-bottom: 2px solid rgba(255,255,255,0.3);
            padding-bottom: 10px;
            margin-top: 0;
        }

        /* Skill bars */
        .skill-container {
            margin-bottom: 15px;
        }
        
        .skill-name {
            display: inline-block;
            width: 100px;
            font-weight: 600;
        }
        
        .skill-bar {
            display: inline-block;
            width: calc(100% - 110px);
            background: rgba(0,0,0,0.2);
            border-radius: 10px;
            overflow: hidden;
            vertical-align: middle;
        }
        
        .skill-level {
            height: 10px;
            background: #fff;
            border-radius: 10px;
        }

        .projects-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 20px;
        }

        .project-card {
            background: rgba(0,0,0,0.2);
            padding: 20px;
            border-radius: 10px;
            transition: transform 0.3s;
        }

        .project-card:hover {
            transform: translateY(-5px);
        }

        .buttons {
            position: fixed;
            bottom: 30px;
            right: 30px;
            display: flex;
            gap: 15px;
            z-index: 100;
        }

        button, .btn {
            padding: 12px 24px;
            border: none;
            border-radius: 25px;
            background: #ffffff;
            color: var(--primary-color);
            font-size: 1em;
            font-weight: 600;
            cursor: pointer;
            box-shadow: 0 4px 15px rgba(0,0,0,0.2);
            transition: all 0.3s;
            text-decoration: none;
        }

        button:hover, .btn:hover {
            background: var(--bg-color);
            color: #ffffff;
        }

        /* Animations */
        @keyframes fadeInDown {
            from { opacity: 0; transform: translateY(-30px); }
            to { opacity: 1; transform: translateY(0); }
        }

        @keyframes fadeInUp {
            from { opacity: 0; transform: translateY(30px); }
            to { opacity: 1; transform: translateY(0); }
        }

        /* 
         * VIVA POINT: @media print CSS hides non-printable elements.
         * When window.print() is called, these styles are applied.
         */
        @media print {
            body {
                background: white;
                color: black;
            }
            .buttons {
                display: none; /* Hide print and back buttons during print */
            }
            .section {
                box-shadow: none;
                border: 1px solid #ccc;
                color: black;
                background: white;
            }
            header h1, header p {
                text-shadow: none;
                color: black;
            }
            .skill-bar {
                background: #eee;
            }
            .skill-level {
                background: #333;
            }
        }
    </style>

    <div class="container">
        <header>
            <h1>Mrigaj Shaw</h1>
            <p>B.Tech CST, IIEST Shibpur</p>
        </header>

        <div class="section">
            <h2>About Me</h2>
            <p>I am a passionate computer science student with a keen interest in web development, software engineering, and solving complex problems. I love building beautiful and responsive web applications.</p>
        </div>

        <div class="section">
            <h2>Skills</h2>
            <div class="skill-container">
                <span class="skill-name">HTML/CSS</span>
                <div class="skill-bar"><div class="skill-level" style="width: 90%;"></div></div>
            </div>
            <div class="skill-container">
                <span class="skill-name">JavaScript</span>
                <div class="skill-bar"><div class="skill-level" style="width: 85%;"></div></div>
            </div>
            <div class="skill-container">
                <span class="skill-name">Java</span>
                <div class="skill-bar"><div class="skill-level" style="width: 80%;"></div></div>
            </div>
            <div class="skill-container">
                <span class="skill-name">C++</span>
                <div class="skill-bar"><div class="skill-level" style="width: 75%;"></div></div>
            </div>
        </div>

        <div class="section">
            <h2>Projects</h2>
            <div class="projects-grid">
                <div class="project-card">
                    <h3>Portfolio Website</h3>
                    <p>A personal portfolio built using HTML, CSS, and vanilla JavaScript showcasing my skills and projects.</p>
                </div>
                <div class="project-card">
                    <h3>E-Commerce App</h3>
                    <p>A full-stack e-commerce application with a React frontend and Node.js backend.</p>
                </div>
                <div class="project-card">
                    <h3>Library Management</h3>
                    <p>A Java-based desktop application for managing library books and member records.</p>
                </div>
            </div>
        </div>

        <div class="section">
            <h2>Contact</h2>
            <p>Email: mrigaj.shaw@example.com</p>
            <p>LinkedIn: linkedin.com/in/mrigajshaw</p>
            <p>GitHub: github.com/mrigajshaw</p>
        </div>
    </div>

    <!-- Floating Buttons -->
    <div class="buttons">
        <button id="printBtn">Print Portfolio</button>
        <button onclick="window.history.back()">Go Back</button>
    </div>
`);
