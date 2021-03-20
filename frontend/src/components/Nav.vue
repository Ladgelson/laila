<template>
    <div>
        <ul class="nav blue">
            <li class="nav-item col-2 justify-content-start">
                <a href="/">
                    <img class="navImg" src="./../assets/cat-svgrepo-com.svg" />
                </a>
            </li>
        </ul>
    </div>
</template>

<script>

</script>

<style>
.navImg {
    height: 45px;
    width: 45px;
    position: absolute;
    left: 15px;
    top: 5px;
    border-radius: 20px;
}

.blue {
    height: 60px;
    background: #323031;
    margin: 0;
}

a.nav-link.active {
    padding-left: 0;
    padding-right: 0;
}

.nav-item {
    padding-left: 0px;
}

</style>