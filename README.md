<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedInKhaled][linkedin-khaled-shield]][linkedin-khaled-url]


<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
      <li><a href="#about-the-project">About The Project</a>
      <li><a href="#Implementation">Implementation</a></li>
      <li><a href="#license">License</a></li>
      <li><a href="#contact">Contact</a></li>
      <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

The project was to develop an embedded system to supervise the operation of a weather station. The hardware platform used to deploy the OS is the NXP's FRDM K64F board.


## Implementation

The embedded system operates by receiving three different input signals. The first signal is a Digital square wave input that represents the wind anemometer. The second signal corresponds to a rain sensor, the third and final input represents a thermometer. 0 to 3.3 volts analog signal is handled in the same way as the rain sensor signal. The signal is converted by using a different ADC (ADC0), a different channel, and a different semaphore. Finally, taskprint was created to trigger the conversion on the channel used and then the values are transmitted serially to be printed on a screen

## Dependencies 

IAR EW for ARM 7.20.2
Keil MDK-ARM 5.11.1.0
Kinetis Design Studio 1.1.0
Kinetis SDK 1.0.0
MICRIUM
Micrium Product Version
uC/CPU 1.30.01
uC/LIB 1.38.00
uC/OS-III 3.04.0



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

Khaled Alamin - [@LinkedIn](https://www.linkedin.com/in/khaled-alamin/)
<!--Project Link: [https://github.com/your_username/repo_name](https://github.com/your_username/repo_name)-->


<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements
* [GitHub Emoji Cheat Sheet](https://www.webpagefx.com/tools/emoji-cheat-sheet)
* [Img Shields](https://shields.io)
* [Choose an Open Source License](https://choosealicense.com)
* [GitHub Pages](https://pages.github.com)
* [Animate.css](https://daneden.github.io/animate.css)
* [Loaders.css](https://connoratherton.com/loaders)
* [Slick Carousel](https://kenwheeler.github.io/slick)
* [Smooth Scroll](https://github.com/cferdinandi/smooth-scroll)
* [Sticky Kit](http://leafo.net/sticky-kit)
* [JVectorMap](http://jvectormap.com)
* [Font Awesome](https://fontawesome.com)



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/othneildrew/Best-README-Template.svg?style=for-the-badge
[contributors-url]: https://github.com/KhaledAlamin/Huawei_embedded_dnn/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/othneildrew/Best-README-Template.svg?style=for-the-badge
[forks-url]: https://github.com/KhaledAlamin/Huawei_embedded_dnn/network/members
[stars-shield]: https://img.shields.io/github/stars/othneildrew/Best-README-Template.svg?style=for-the-badge
[stars-url]: https://github.com/KhaledAlamin/Huawei_embedded_dnn/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=for-the-badge
[issues-url]: https://github.com/KhaledAlamin/Huawei_embedded_dnn/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/KhaledAlamin/Huawei_embedded_dnn/blob/main/LICENSE.txt
[linkedin-khaled-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-khaled-url]: https://www.linkedin.com/in/khaled-alamin/
[linkedin-eyas-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-eyas-url]: https://www.linkedin.com/in/EyasAli/
